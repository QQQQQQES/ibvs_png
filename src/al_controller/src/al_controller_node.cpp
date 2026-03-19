#include <ros/ros.h>
#include "al_controller/al_controller.h"
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <std_msgs/Float64.h>

class ALControllerNode {
public:
  ALControllerNode() : nh_("~"), odom_received_(false), desired_vel_dir_received_(false),
                       image_error_received_(false), last_ex_(0.0), current_ex_(0.0), state_initialized_(false) {
    // Initialize AL controller
    controller_ = std::make_shared<al_controller::ALController>();
    controller_->initialize(nh_);

    // Initialize velocity
    current_velocity_.setZero();
    smoothed_v_cmd_.setZero();

    // Load node parameters
    nh_.param("control_rate", control_rate_, 100.0);
    nh_.param("desired_speed", desired_speed_, 5.0);
    nh_.param("dt", dt_, 0.01);
    nh_.param("max_acceleration", max_acceleration_, 3.0);
    nh_.param("k_feedback", k_feedback_, 0.5);
    nh_.param("ka", ka_, 0.3);

    // Load PD control parameters for yaw
    nh_.param("kp_yaw", kp_yaw_, 0.0005);
    nh_.param("kd_yaw", kd_yaw_, 0.00001);

    // Initialize subscribers
    desired_vel_dir_sub_ = nh_.subscribe("/los_calculator/desired_velocity_direction", 10,
                                         &ALControllerNode::desiredVelDirCallback, this);
    uav_odom_sub_ = nh_.subscribe("/iris_0/mavros/local_position/odom", 10,
                                  &ALControllerNode::odomCallback, this);
    thrust_model_sub_ = nh_.subscribe("/px4ctrl/thrust_model", 10,
                                      &ALControllerNode::thrustModelCallback, this);
    image_error_sub_ = nh_.subscribe("/target_error", 10,
                                     &ALControllerNode::imageErrorCallback, this);

    // Initialize publishers
    thrust_pub_ = nh_.advertise<geometry_msgs::Vector3>("/al_controller/thrust_direction", 10);
    thrust_value_pub_ = nh_.advertise<geometry_msgs::Vector3>("/al_controller/thrust_value", 10);
    omega_pub_ = nh_.advertise<geometry_msgs::Vector3>("/al_controller/angular_velocity", 10);
    attitude_target_pub_ = nh_.advertise<mavros_msgs::AttitudeTarget>("/iris_0/mavros/setpoint_raw/attitude", 10);
    acceleration_pub_ = nh_.advertise<geometry_msgs::Vector3>("/al_controller/desired_acceleration", 10);
    velocity_pub_ = nh_.advertise<geometry_msgs::Vector3>("/al_controller/desired_velocity", 10);
    yaw_rate_pub_ = nh_.advertise<std_msgs::Float64>("/al_controller/yaw_rate_sp", 10);

    // Create control timer
    control_timer_ = nh_.createTimer(ros::Duration(1.0 / control_rate_),
                                     &ALControllerNode::controlTimerCallback, this);

    ROS_INFO("AL Controller Node initialized");
    ROS_INFO("  Control rate: %.1f Hz", control_rate_);
  }

private:
  void desiredVelDirCallback(const geometry_msgs::Vector3::ConstPtr& msg) {
    latest_desired_vel_dir_ = *msg;
    if (!desired_vel_dir_received_) {
      ROS_INFO("First desired_velocity_direction received: n_vd=[%.2f, %.2f, %.2f]",
               msg->x, msg->y, msg->z);
    }
    desired_vel_dir_received_ = true;
  }

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    current_velocity_(0) = msg->twist.twist.linear.x;
    current_velocity_(1) = msg->twist.twist.linear.y;
    current_velocity_(2) = msg->twist.twist.linear.z;

    Eigen::Quaterniond orientation(msg->pose.pose.orientation.w,
                                   msg->pose.pose.orientation.x,
                                   msg->pose.pose.orientation.y,
                                   msg->pose.pose.orientation.z);
    controller_->updateUAVOrientation(orientation);

    if (!odom_received_) {
      ROS_INFO("First odom received");
    }
    odom_received_ = true;
  }

  void thrustModelCallback(const std_msgs::Float64::ConstPtr& msg) {
    controller_->setThr2Acc(msg->data);
    // ROS_DEBUG_THROTTLE(5.0, "Updated thr2acc: %.3f", msg->data);
  }

  void imageErrorCallback(const geometry_msgs::Vector3::ConstPtr& msg) {
    current_ex_ = msg->x;
    if (!image_error_received_) {
      ROS_INFO("First image error received: ex=%.4f", current_ex_);
    }
    image_error_received_ = true;
  }

  void controlTimerCallback(const ros::TimerEvent&) {
    if (!desired_vel_dir_received_ || !odom_received_) {
      ROS_WARN_THROTTLE(2.0, "Waiting for data: desired_vel_dir=%d, odom=%d",
                        desired_vel_dir_received_, odom_received_);
      return;
    }

    Eigen::Vector3d n_vd(latest_desired_vel_dir_.x,
                         latest_desired_vel_dir_.y,
                         latest_desired_vel_dir_.z);
    n_vd.normalize();

    double v_now_mag = current_velocity_.norm();
    double v_d_mag = v_now_mag + ka_;
    Eigen::Vector3d v_cmd = n_vd * v_d_mag;

    if(!state_initialized_) {
      last_ex_ = std::isnan(current_ex_) ? 0.0 : current_ex_;
      state_initialized_ = true;
    }

    if (image_error_received_) {
      double ex_dot = (current_ex_ - last_ex_) / dt_;
      double yaw_rate_sp = -(kp_yaw_ * current_ex_ + kd_yaw_ * ex_dot);
      publishYawRate(yaw_rate_sp);
      last_ex_ = current_ex_;
    }

    // Eigen::Vector3d delta_v = v_cmd - smoothed_v_cmd_;
    // double max_delta_v = max_acceleration_ * dt_;
    // if (delta_v.norm() > max_delta_v) {
    //     delta_v = delta_v.normalized() * max_delta_v;
    // }

    // Eigen::Vector3d prev_smoothed_v_cmd = smoothed_v_cmd_;
    // smoothed_v_cmd_ += delta_v;

    // Eigen::Vector3d a_d_feedforward = (smoothed_v_cmd_ - prev_smoothed_v_cmd) / dt_;

    // Eigen::Vector3d velocity_error = smoothed_v_cmd_ - current_velocity_;
    // Eigen::Vector3d a_d = a_d_feedforward + k_feedback_ * velocity_error;

    // Eigen::Matrix3d R_b_e = controller_->getRotationMatrix();

    // al_controller::ALController::AttitudeCommand cmd =
    //     controller_->computeAttitudeCommand(a_d, R_b_e);

    // publishThrustDirection(cmd.n_fd);
    // publishThrustValue(cmd.thrust);
    // publishAngularVelocity(cmd.omega_d);
    // publishAttitudeTarget(cmd);
    // publishAcceleration(a_d);
    publishVelocity(v_cmd);
  }

  void publishThrustDirection(const Eigen::Vector3d& n_fd) {
    geometry_msgs::Vector3 msg;
    msg.x = n_fd(0);
    msg.y = n_fd(1);
    msg.z = n_fd(2);
    thrust_pub_.publish(msg);
  }

  void publishThrustValue(double thrust) {
    geometry_msgs::Vector3 msg;
    msg.x = thrust;
    msg.y = 0.0;
    msg.z = 0.0;
    thrust_value_pub_.publish(msg);
  }

  void publishAngularVelocity(const Eigen::Vector3d& omega_d) {
    geometry_msgs::Vector3 msg;
    msg.x = omega_d(0);
    msg.y = omega_d(1);
    msg.z = omega_d(2);
    omega_pub_.publish(msg);
  }

  void publishAcceleration(const Eigen::Vector3d& a_d) {
    geometry_msgs::Vector3 msg;
    msg.x = a_d(0);
    msg.y = a_d(1);
    msg.z = a_d(2);
    acceleration_pub_.publish(msg);
  }

  void publishVelocity(const Eigen::Vector3d& v_cmd) {
    geometry_msgs::Vector3 msg;
    msg.x = v_cmd(0);
    msg.y = v_cmd(1);
    msg.z = v_cmd(2);
    velocity_pub_.publish(msg);
  }

  void publishYawRate(double yaw_rate_sp) {
    std_msgs::Float64 msg;
    msg.data = yaw_rate_sp;
    yaw_rate_pub_.publish(msg);
  }

  void publishAttitudeTarget(const al_controller::ALController::AttitudeCommand& cmd) {
    mavros_msgs::AttitudeTarget msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "base_link";

    msg.type_mask = mavros_msgs::AttitudeTarget::IGNORE_ATTITUDE;

    msg.body_rate.x = cmd.omega_d(0);
    msg.body_rate.y = cmd.omega_d(1);
    msg.body_rate.z = cmd.omega_d(2);

    msg.thrust = cmd.thrust;

    attitude_target_pub_.publish(msg);
  }

  ros::NodeHandle nh_;
  std::shared_ptr<al_controller::ALController> controller_;

  // Subscribers
  ros::Subscriber desired_vel_dir_sub_;
  ros::Subscriber uav_odom_sub_;
  ros::Subscriber thrust_model_sub_;
  ros::Subscriber image_error_sub_;

  // Publishers
  ros::Publisher thrust_pub_;
  ros::Publisher thrust_value_pub_;
  ros::Publisher omega_pub_;
  ros::Publisher attitude_target_pub_;
  ros::Publisher acceleration_pub_;
  ros::Publisher velocity_pub_;
  ros::Publisher yaw_rate_pub_;

  // Timer
  ros::Timer control_timer_;

  // Latest data
  geometry_msgs::Vector3 latest_desired_vel_dir_;
  Eigen::Vector3d current_velocity_;
  Eigen::Vector3d smoothed_v_cmd_;
  bool desired_vel_dir_received_;
  bool odom_received_;
  bool image_error_received_;
  bool state_initialized_;

  // Image error state
  double last_ex_;
  double current_ex_;

  // Parameters
  double control_rate_;
  double desired_speed_;
  double dt_;
  double max_acceleration_;
  double k_feedback_;
  double ka_;
  double kp_yaw_;
  double kd_yaw_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "al_controller_node");
  ALControllerNode node;
  ros::spin();
  return 0;
}
