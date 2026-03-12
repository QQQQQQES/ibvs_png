#include <ros/ros.h>
#include "los_calculator/los_calculator.h"
#include <ibvs_msgs/TargetState.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64MultiArray.h>

class LOSCalculatorNode {
public:
  LOSCalculatorNode() : nh_("~"), target_received_(false), odom_received_(false) {
    // Initialize LOS calculator
    calculator_ = std::make_shared<los_calculator::LOSCalculator>();
    calculator_->initialize(nh_);

    // Load node parameters
    nh_.param("control_rate", control_rate_, 100.0);

    // Initialize subscribers
    target_error_sub_ = nh_.subscribe("/target_error", 10,
                                      &LOSCalculatorNode::targetErrorCallback, this);
    uav_odom_sub_ = nh_.subscribe("/iris_0/mavros/local_position/odom", 10,
                                  &LOSCalculatorNode::odomCallback, this);

    // Initialize publishers
    los_rate_pub_ = nh_.advertise<geometry_msgs::Vector3>("/los_calculator/los_rate", 10);
    los_angles_pub_ = nh_.advertise<geometry_msgs::Vector3>("/los_calculator/los_angles", 10);
    lead_angles_pub_ = nh_.advertise<geometry_msgs::Vector3>("/los_calculator/lead_angles", 10);
    target_normal_pub_ = nh_.advertise<geometry_msgs::Vector3>("/los_calculator/target_normal", 10);
    desired_velocity_dir_pub_ = nh_.advertise<geometry_msgs::Vector3>("/los_calculator/desired_velocity_direction", 10);

    // Create control timer
    control_timer_ = nh_.createTimer(ros::Duration(1.0 / control_rate_),
                                     &LOSCalculatorNode::controlTimerCallback, this);

    ROS_INFO("LOS Calculator Node initialized");
    ROS_INFO("  Control rate: %.1f Hz", control_rate_);
  }

private:
  void targetErrorCallback(const geometry_msgs::Vector3::ConstPtr& msg) {
    latest_target_error_ = *msg;
    if (!target_received_) {
      ROS_INFO("First target_error received: err_x=%.2f, err_y=%.2f", msg->x, msg->y);
    }
    target_received_ = true;
  }

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    // Update UAV velocity
    Eigen::Vector3d velocity(msg->twist.twist.linear.x,
                            msg->twist.twist.linear.y,
                            msg->twist.twist.linear.z);
    calculator_->updateUAVVelocity(velocity);

    // Update UAV orientation
    Eigen::Quaterniond orientation(msg->pose.pose.orientation.w,
                                   msg->pose.pose.orientation.x,
                                   msg->pose.pose.orientation.y,
                                   msg->pose.pose.orientation.z);
    calculator_->updateUAVOrientation(orientation);
    if (!odom_received_) {
      ROS_INFO("First odom received");
    }
    odom_received_ = true;
  }

  void controlTimerCallback(const ros::TimerEvent&) {
    // if (!target_received_ || !odom_received_) {
    //   ROS_WARN_THROTTLE(2.0, "Waiting for data: target_received=%d, odom_received=%d",
    //                     target_received_, odom_received_);
    //   return;
    // }

    // Use error directly from /target_error topic
    double err_x = latest_target_error_.x;
    double err_y = latest_target_error_.y;

    // Compute LOS rate
    Eigen::Vector2d los_rate = calculator_->computeLOSRate(err_x, err_y);

    // Get LOS angles
    Eigen::Vector2d los_angles = calculator_->getLOSAngles();

    // Get lead angles
    Eigen::Vector2d lead_angles = calculator_->getLeadAngles();

    // Get target normal
    Eigen::Vector3d target_normal = calculator_->getTargetNormal();

    // Get desired velocity direction
    Eigen::Vector3d desired_vel_dir = calculator_->getDesiredVelocityDirection();

    // Publish results
    publishLOSRate(los_rate);
    publishLOSAngles(los_angles);
    publishLeadAngles(lead_angles);
    publishTargetNormal(target_normal);
    publishDesiredVelocityDirection(desired_vel_dir);

    // ROS_INFO("LOS Rate: dq_y/dt=%.3f rad/s, dq_z/dt=%.3f rad/s",
    //          los_rate(0), los_rate(1));
  }

  void publishLOSRate(const Eigen::Vector2d& los_rate) {
    geometry_msgs::Vector3 msg;
    msg.x = los_rate(0);  // dq_y_dt
    msg.y = los_rate(1);  // dq_z_dt
    msg.z = 0.0;
    los_rate_pub_.publish(msg);
  }

  void publishLOSAngles(const Eigen::Vector2d& los_angles) {
    geometry_msgs::Vector3 msg;
    msg.x = los_angles(0);  // q_y
    msg.y = los_angles(1);  // q_z
    msg.z = 0.0;
    los_angles_pub_.publish(msg);
  }

  void publishLeadAngles(const Eigen::Vector2d& lead_angles) {
    geometry_msgs::Vector3 msg;
    msg.x = lead_angles(0);  // sigma_y
    msg.y = lead_angles(1);  // sigma_z
    msg.z = 0.0;
    lead_angles_pub_.publish(msg);
  }

  void publishTargetNormal(const Eigen::Vector3d& target_normal) {
    geometry_msgs::Vector3 msg;
    msg.x = target_normal(0);
    msg.y = target_normal(1);
    msg.z = target_normal(2);
    target_normal_pub_.publish(msg);
  }

  void publishDesiredVelocityDirection(const Eigen::Vector3d& desired_vel_dir) {
    geometry_msgs::Vector3 msg;
    msg.x = desired_vel_dir(0);
    msg.y = desired_vel_dir(1);
    msg.z = desired_vel_dir(2);
    desired_velocity_dir_pub_.publish(msg);
  }

  ros::NodeHandle nh_;
  std::shared_ptr<los_calculator::LOSCalculator> calculator_;

  // Subscribers
  ros::Subscriber target_error_sub_;
  ros::Subscriber uav_odom_sub_;

  // Publishers
  ros::Publisher los_rate_pub_;
  ros::Publisher los_angles_pub_;
  ros::Publisher lead_angles_pub_;
  ros::Publisher target_normal_pub_;
  ros::Publisher desired_velocity_dir_pub_;

  // Timer
  ros::Timer control_timer_;

  // Latest data
  geometry_msgs::Vector3 latest_target_error_;
  bool target_received_;
  bool odom_received_;

  // Parameters
  double control_rate_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "los_calculator_node");
  LOSCalculatorNode node;
  ros::spin();
  return 0;
}
