#include <ros/ros.h>
#include <ibvs_msgs/TargetState.h>
#include <ibvs_msgs/ControlCommand.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>
#include "visual_servo_controller/ibvs_controller.h"

class VisualServoControllerNode {
public:
  VisualServoControllerNode() : nh_("~") {
    // Initialize controller
    controller_ = std::make_shared<visual_servo_controller::IBVSController>();
    controller_->initialize(nh_);

    // Load parameters
    loadParameters();

    // Initialize publishers and subscribers
    target_state_sub_ = nh_.subscribe("/target_state", 10,
                                      &VisualServoControllerNode::targetStateCallback, this);
    odom_sub_ = nh_.subscribe("/mavros/local_position/odom", 10,
                              &VisualServoControllerNode::odomCallback, this);
    control_cmd_pub_ = nh_.advertise<ibvs_msgs::ControlCommand>("/control_command", 10);
    velocity_cmd_pub_ = nh_.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel", 10);

    ROS_INFO("Visual servo controller node initialized");
  }

private:
  void loadParameters() {
    // TODO: Load ROS parameters
  }

  void targetStateCallback(const ibvs_msgs::TargetState::ConstPtr& msg) {
    latest_target_state_ = *msg;
    has_target_state_ = true;
    computeAndPublishControl();
  }

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    current_velocity_.header = msg->header;
    current_velocity_.twist = msg->twist.twist;
    has_odometry_ = true;
  }

  void computeAndPublishControl() {
    if (!has_target_state_ || !has_odometry_) {
      return;
    }

    ibvs_msgs::ControlCommand control_cmd;
    if (controller_->computeControlCommand(latest_target_state_, current_velocity_, control_cmd)) {
      control_cmd_pub_.publish(control_cmd);

      // Convert to velocity command
      geometry_msgs::TwistStamped vel_cmd;
      vel_cmd.header.stamp = ros::Time::now();
      vel_cmd.twist.linear = control_cmd.linear_velocity;
      vel_cmd.twist.angular = control_cmd.angular_velocity;
      velocity_cmd_pub_.publish(vel_cmd);
    }
  }

  ros::NodeHandle nh_;
  ros::Subscriber target_state_sub_;
  ros::Subscriber odom_sub_;
  ros::Publisher control_cmd_pub_;
  ros::Publisher velocity_cmd_pub_;

  std::shared_ptr<visual_servo_controller::IBVSController> controller_;

  ibvs_msgs::TargetState latest_target_state_;
  geometry_msgs::TwistStamped current_velocity_;
  bool has_target_state_ = false;
  bool has_odometry_ = false;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "visual_servo_controller_node");
  VisualServoControllerNode node;
  ros::spin();
  return 0;
}
