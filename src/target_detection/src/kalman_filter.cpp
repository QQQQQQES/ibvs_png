#include "target_detection/kalman_filter.h"

namespace target_detection {

DualKalmanFilter::DualKalmanFilter()
  : dt_(0.033),  // 30Hz default
    initialized_(false) {

  // Initialize image plane state (u, v, u_dot, v_dot)
  state_image_ = Eigen::Vector4d::Zero();
  P_image_ = Eigen::Matrix4d::Identity();

  // Initialize depth state (Z, Z_dot)
  state_depth_ = Eigen::Vector2d::Zero();
  P_depth_ = Eigen::Matrix2d::Identity();
}

DualKalmanFilter::~DualKalmanFilter() {
}

void DualKalmanFilter::initialize(double process_variance, double measurement_variance, double dt) {
  dt_ = dt;

  // Image plane filter setup
  Q_image_ = Eigen::Matrix4d::Identity() * process_variance;
  R_image_ = Eigen::Matrix2d::Identity() * measurement_variance;

  // State transition matrix for image plane (constant velocity model)
  F_image_ << 1.0, 0.0, dt_, 0.0,
              0.0, 1.0, 0.0, dt_,
              0.0, 0.0, 1.0, 0.0,
              0.0, 0.0, 0.0, 1.0;

  // Measurement matrix for image plane (measure position only)
  H_image_ << 1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0;

  // Depth filter setup
  Q_depth_ = Eigen::Matrix2d::Identity() * process_variance;
  R_depth_ = measurement_variance;

  // State transition matrix for depth
  F_depth_ << 1.0, dt_,
              0.0, 1.0;

  // Measurement matrix for depth
  H_depth_ << 1.0, 0.0;

  initialized_ = false;
}

Eigen::Vector4d DualKalmanFilter::updateImagePlane(const Eigen::Vector2d& measurement) {
  if (!initialized_) {
    // Initialize state with first measurement
    state_image_ << measurement(0), measurement(1), 0.0, 0.0;
    P_image_ = Eigen::Matrix4d::Identity();
    initialized_ = true;
    return state_image_;
  }

  // Prediction step
  Eigen::Vector4d state_pred = F_image_ * state_image_;
  Eigen::Matrix4d P_pred = F_image_ * P_image_ * F_image_.transpose() + Q_image_;

  // Update step
  Eigen::Vector2d innovation = measurement - H_image_ * state_pred;
  Eigen::Matrix2d S = H_image_ * P_pred * H_image_.transpose() + R_image_;
  Eigen::Matrix<double, 4, 2> K = P_pred * H_image_.transpose() * S.inverse();

  state_image_ = state_pred + K * innovation;
  P_image_ = (Eigen::Matrix4d::Identity() - K * H_image_) * P_pred;

  return state_image_;
}

Eigen::Vector2d DualKalmanFilter::updateDepth(double depth_measurement) {
  if (state_depth_(0) == 0.0) {
    // Initialize depth state
    state_depth_ << depth_measurement, 0.0;
    P_depth_ = Eigen::Matrix2d::Identity();
    return state_depth_;
  }

  // Prediction step
  Eigen::Vector2d state_pred = F_depth_ * state_depth_;
  Eigen::Matrix2d P_pred = F_depth_ * P_depth_ * F_depth_.transpose() + Q_depth_;

  // Update step
  double innovation = depth_measurement - H_depth_ * state_pred;
  double S = (H_depth_ * P_pred * H_depth_.transpose())(0, 0) + R_depth_;
  Eigen::Vector2d K = P_pred * H_depth_.transpose() / S;

  state_depth_ = state_pred + K * innovation;
  P_depth_ = (Eigen::Matrix2d::Identity() - K * H_depth_) * P_pred;

  return state_depth_;
}

void DualKalmanFilter::reset() {
  state_image_ = Eigen::Vector4d::Zero();
  state_depth_ = Eigen::Vector2d::Zero();
  P_image_ = Eigen::Matrix4d::Identity();
  P_depth_ = Eigen::Matrix2d::Identity();
  initialized_ = false;
}

} // namespace target_detection
