#ifndef VISUAL_SERVO_CONTROLLER_IBVS_CONTROLLER_H
#define VISUAL_SERVO_CONTROLLER_IBVS_CONTROLLER_H

#include <ros/ros.h>
#include <Eigen/Dense>
#include <ibvs_msgs/TargetState.h>
#include <ibvs_msgs/ControlCommand.h>
#include <geometry_msgs/TwistStamped.h>

namespace visual_servo_controller {

class IBVSController {
public:
  IBVSController();
  ~IBVSController();

  bool initialize(const ros::NodeHandle& nh);

  bool computeControlCommand(const ibvs_msgs::TargetState& target_state,
                             const geometry_msgs::TwistStamped& current_velocity,
                             ibvs_msgs::ControlCommand& control_cmd);

  void setControlGains(double lambda, const Eigen::Matrix3d& K_v, const Eigen::Matrix3d& K_omega);

  void setDesiredImagePosition(double u_d, double v_d);

private:
  // Control gains
  double lambda_;
  Eigen::Matrix3d K_v_;
  Eigen::Matrix3d K_omega_;

  // Desired image position
  Eigen::Vector2d desired_position_;

  // Camera parameters
  double focal_length_;
  Eigen::Vector2d principal_point_;

  // Compute image Jacobian
  Eigen::MatrixXd computeImageJacobian(const Eigen::Vector2d& feature_point, double depth);

  // Compute velocity command
  Eigen::VectorXd computeVelocityCommand(const Eigen::VectorXd& feature_error,
                                         const Eigen::MatrixXd& image_jacobian);

  // TODO: Implement IBVS control law
};

} // namespace visual_servo_controller

#endif // VISUAL_SERVO_CONTROLLER_IBVS_CONTROLLER_H
