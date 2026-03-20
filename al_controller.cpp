#include "al_controller/al_controller.h"
#include <cmath>

namespace al_controller {

ALController::ALController()
  : thr2acc_(12.727),
    thrust_min_(0.3),
    thrust_max_(0.95),
    max_thrust_acc_(200.0) {
  uav_orientation_ = Eigen::Quaterniond::Identity();
  R_b_e_ = Eigen::Matrix3d::Identity();
}

ALController::~ALController() {
}

bool ALController::initialize(const ros::NodeHandle& nh) {
  nh.param("thr2acc", thr2acc_, 12.727);
  nh.param("thrust_min", thrust_min_, 0.3);
  nh.param("thrust_max", thrust_max_, 0.95);
  nh.param("max_thrust_acc", max_thrust_acc_, 200.0);

  ROS_INFO("AL Controller initialized:");
  ROS_INFO("  thr2acc: %.3f", thr2acc_);
  ROS_INFO("  thrust range: [%.2f, %.2f]", thrust_min_, thrust_max_);

  return true;
}

ALController::AttitudeCommand ALController::computeAttitudeCommand(
    const Eigen::Vector3d& a_d,
    const Eigen::Matrix3d& R_b_e) {
  AttitudeCommand cmd;

  Eigen::Vector3d gravity(0, 0, -GRAVITY);
  Eigen::Vector3d thrust_vec = a_d - gravity;

  Eigen::Vector3d n_f = R_b_e.col(2);

  double f_d_projection = std::max(n_f.dot(thrust_vec), 0.0);
  double f_d = std::min(f_d_projection, max_thrust_acc_);

  double thrust_norm = thrust_vec.norm();
  if (thrust_norm < 1e-6) {
    cmd.n_fd = Eigen::Vector3d(0, 0, 1);  // 悬停：升力向上
  } else {
    cmd.n_fd = thrust_vec / thrust_norm;
  }

  cmd.thrust = f_d / thr2acc_;
  // std::cout << "thr2acc_ is %f" << thr2acc_ << std::endl;
  cmd.thrust = clamp(cmd.thrust, thrust_min_, thrust_max_);

  Eigen::Matrix3d R_tilt = computeAttitudeRotation(cmd.n_fd);
  Eigen::Matrix3d R_d = R_tilt * R_b_e;

  cmd.omega_d = computeAngularVelocity(R_d, R_b_e);

  return cmd;
}

Eigen::Matrix3d ALController::computeAttitudeRotation(const Eigen::Vector3d& n_fd) {
  Eigen::Vector3d n_f = R_b_e_.col(2);
    
  Eigen::Vector3d r = n_f.cross(n_fd);
  double r_norm = r.norm();

  if (r_norm < 1e-6) {
    double dot_product = n_f.dot(n_fd);
    if (dot_product > 0) {
      return Eigen::Matrix3d::Identity();
    } else {
      Eigen::Vector3d arbitrary_axis;
      if (std::abs(n_f(0)) < 0.9) {
        arbitrary_axis = Eigen::Vector3d(1, 0, 0);
      } else {
        arbitrary_axis = Eigen::Vector3d(0, 1, 0);
      }
      r = n_f.cross(arbitrary_axis).normalized();
      Eigen::Matrix3d r_skew = skewSymmetric(r);
      return Eigen::Matrix3d::Identity() + 2.0 * r_skew * r_skew;
    }
  }

  r = r / r_norm;
  double dot_product = n_f.dot(n_fd);
  double phi = std::acos(clamp(dot_product, -1.0, 1.0));

  Eigen::Matrix3d r_skew = skewSymmetric(r);  

  //Rodrigues
  Eigen::Matrix3d R_tilt = Eigen::Matrix3d::Identity()
                         + std::sin(phi) * r_skew
                         + (1 - std::cos(phi)) * r_skew * r_skew;
  return R_tilt;//have no yaw
}

Eigen::Vector3d ALController::computeAngularVelocity(const Eigen::Matrix3d& R_d,
                                                     const Eigen::Matrix3d& R_b_e) {
  Eigen::Matrix3d R_error_mat = R_d.transpose() * R_b_e - R_b_e.transpose() * R_d;

  Eigen::Vector3d omega_d;
  omega_d(0) = -0.5 * (R_error_mat(2, 1) - R_error_mat(1, 2));
  omega_d(1) = -0.5 * (R_error_mat(0, 2) - R_error_mat(2, 0));
  omega_d(2) = -0.5 * (R_error_mat(1, 0) - R_error_mat(0, 1));

  return omega_d;
}

Eigen::Matrix3d ALController::skewSymmetric(const Eigen::Vector3d& v) {
  Eigen::Matrix3d skew;
  skew <<     0,  -v(2),   v(1),
           v(2),      0,  -v(0),
          -v(1),   v(0),      0;
  return skew;
}

double ALController::clamp(double value, double min_val, double max_val) {
  return std::max(min_val, std::min(max_val, value));
}

void ALController::updateUAVOrientation(const Eigen::Quaterniond& orientation) {
  uav_orientation_ = orientation;
  R_b_e_ = orientation.toRotationMatrix();
}

void ALController::setThr2Acc(double thr2acc) {
  thr2acc_ = thr2acc;
}

double ALController::getThr2Acc() const {
  return thr2acc_;
}

Eigen::Matrix3d ALController::getRotationMatrix() const {
  return R_b_e_;
}

} // namespace al_controller
