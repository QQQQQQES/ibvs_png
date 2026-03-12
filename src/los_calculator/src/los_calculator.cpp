#include "los_calculator/los_calculator.h"
#include <cmath>

namespace los_calculator {

LOSCalculator::LOSCalculator()
  : K_(2.0),
    v_m_(5.0),
    focal_length_(554.0),
    depth_(5.0),
    dt_(0.01),
    q_y_(0.0),
    q_z_(0.0),
    sigma_y_d(0.0),
    sigma_z_d(0.0),
    delta_q_y_(0.0),
    delta_q_z_(0.0),
    prev_q_y_(0.0),
    prev_q_z_(0.0),
    prev_sigma_y_actual_(0.0),
    prev_sigma_z_actual_(0.0),
    initialized_(false) {

  uav_velocity_.setZero();
  uav_orientation_ = Eigen::Quaterniond::Identity();
  n_t_.setZero();
}

LOSCalculator::~LOSCalculator() {
}

bool LOSCalculator::initialize(const ros::NodeHandle& nh) {
  // Load parameters from ROS parameter server
  nh.param("png_gain", K_, 2.0);
  nh.param("max_velocity", v_m_, 5.0);
  nh.param("focal_length", focal_length_, 500.0);
  nh.param("target_depth", depth_, 5.0);
  nh.param("time_step", dt_, 0.01);

  ROS_INFO("LOS Calculator initialized:");
  ROS_INFO("  PNG gain K: %.2f", K_);
  ROS_INFO("  Max velocity: %.2f m/s", v_m_);
  ROS_INFO("  Focal length: %.2f px", focal_length_);
  ROS_INFO("  Time step: %.4f s", dt_);

  return true;
}

double LOSCalculator::wrapToPi(double angle) {
  while (angle > M_PI) angle -= 2.0 * M_PI;
  while (angle < -M_PI) angle += 2.0 * M_PI;
  return angle;
}

Eigen::Vector3d LOSCalculator::pixelErrorToNormal(double err_x, double err_y) {
  // 步骤1: 构造相机坐标系下的视线向量
  Eigen::Vector3d n_t_camera(err_x, err_y, focal_length_);
  n_t_camera.normalize();

  // 步骤2: 相机坐标系 -> 机体坐标系转换
  Eigen::Matrix3d R_c_b;
    R_c_b << 0, 0, 1,   // camera z -> body x
            -1, 0, 0,   // camera x -> body -y
            0, -1, 0;  // camera y -> body -z

  Eigen::Vector3d n_t_body = R_c_b * n_t_camera;

  // 步骤3: 机体坐标系 -> ENU世界坐标系转换
  Eigen::Matrix3d R_b_e = uav_orientation_.toRotationMatrix();
  Eigen::Vector3d n_t_enu = R_b_e * n_t_body;

  return n_t_enu;
}

void LOSCalculator::computeLOSAndLeadAngles(const Eigen::Vector3d& n_t) {
  double n_xz = n_t(0);
  double n_yy = n_t(1);
  double n_yz = n_t(2);

  double q_y_curr = std::atan2(n_xz, n_yy);
  double horizontal_component = std::sqrt(n_xz * n_xz + n_yy * n_yy);
  double q_z_curr = std::atan2(n_yz, horizontal_component);

  if (!initialized_) {
    q_y_ = q_y_curr;
    q_z_ = q_z_curr;
    sigma_y_d = q_y_curr;
    sigma_z_d = q_z_curr;
    prev_sigma_y_actual_ = q_y_curr;
    prev_sigma_z_actual_ = q_z_curr;
    initialized_ = true;
    ROS_INFO("LOS Calculator initialized with q_y=%.3f, q_z=%.3f", q_y_curr, q_z_curr);
    return;
  }

  delta_q_y_ = wrapToPi(q_y_curr - q_y_);
  delta_q_z_ = wrapToPi(q_z_curr - q_z_);

  sigma_y_d = K_ * delta_q_y_ + prev_sigma_y_actual_;
  sigma_z_d = K_ * delta_q_z_ + prev_sigma_z_actual_;

  q_y_ = q_y_curr;
  q_z_ = q_z_curr;
  prev_sigma_y_actual_ = sigma_y_d;
  prev_sigma_z_actual_ = sigma_z_d;
}

Eigen::Vector2d LOSCalculator::computeLOSRate(double err_x, double err_y) {
  n_t_ = pixelErrorToNormal(err_x, err_y);

  computeLOSAndLeadAngles(n_t_);

  double dq_y_dt = delta_q_y_ / dt_;
  double dq_z_dt = delta_q_z_ / dt_;

  return Eigen::Vector2d(dq_y_dt, dq_z_dt);
}

Eigen::Vector2d LOSCalculator::getLOSAngles() const {
  return Eigen::Vector2d(q_y_, q_z_);
}

Eigen::Vector2d LOSCalculator::getLeadAngles() const {
  return Eigen::Vector2d(sigma_y_d, sigma_z_d);
}

Eigen::Vector3d LOSCalculator::getTargetNormal() const {
  return n_t_;
}

Eigen::Vector3d LOSCalculator::getDesiredVelocityDirection() const {
  Eigen::Vector3d n_vd;
  n_vd(0) = std::cos(sigma_z_d) * std::sin(sigma_y_d);
  n_vd(1) = std::cos(sigma_z_d) * std::cos(sigma_y_d);
  n_vd(2) = std::sin(sigma_z_d);
  n_vd.normalize();

  return n_vd;
}

void LOSCalculator::updateUAVVelocity(const Eigen::Vector3d& velocity) {
  uav_velocity_ = velocity;
}

void LOSCalculator::setPNGGain(double K) {
  K_ = K;
}

void LOSCalculator::updateUAVOrientation(const Eigen::Quaterniond& orientation) {
  uav_orientation_ = orientation;
}

}
