#include "visual_servo_controller/ibvs_controller.h"

namespace visual_servo_controller {

IBVSController::IBVSController()
  : lambda_(0.5),
    focal_length_(500.0) {
  K_v_ = Eigen::Matrix3d::Identity();
  K_omega_ = Eigen::Matrix3d::Identity();
  desired_position_ = Eigen::Vector2d::Zero();
  principal_point_ = Eigen::Vector2d::Zero();
}

IBVSController::~IBVSController() {
}

bool IBVSController::initialize(const ros::NodeHandle& nh) {
  // TODO: Load parameters from ROS parameter server
  return true;
}

bool IBVSController::computeControlCommand(const ibvs_msgs::TargetState& target_state,
                                           const geometry_msgs::TwistStamped& current_velocity,
                                           ibvs_msgs::ControlCommand& control_cmd) {
  // TODO: Implement IBVS control law
  return false;
}

void IBVSController::setControlGains(double lambda, const Eigen::Matrix3d& K_v,
                                     const Eigen::Matrix3d& K_omega) {
  lambda_ = lambda;
  K_v_ = K_v;
  K_omega_ = K_omega;
}

void IBVSController::setDesiredImagePosition(double u_d, double v_d) {
  desired_position_ << u_d, v_d;
}

Eigen::MatrixXd IBVSController::computeImageJacobian(const Eigen::Vector2d& feature_point,
                                                     double depth) {
  // TODO: Implement image Jacobian computation
  Eigen::MatrixXd L = Eigen::MatrixXd::Zero(2, 6);
  return L;
}

Eigen::VectorXd IBVSController::computeVelocityCommand(const Eigen::VectorXd& feature_error,
                                                       const Eigen::MatrixXd& image_jacobian) {
  // TODO: Implement velocity command computation
  Eigen::VectorXd velocity_cmd = Eigen::VectorXd::Zero(6);
  return velocity_cmd;
}

} // namespace visual_servo_controller
