#include "target_detection/depth_estimator.h"
#include <ros/ros.h>
#include <cmath>

namespace target_detection {

DepthEstimator::DepthEstimator()
  : focal_length_(500.0),
    baseline_(0.12),
    initialized_(false),
    last_depth_(1.0) {
}

DepthEstimator::~DepthEstimator() {
}

void DepthEstimator::initialize(double focal_length, double baseline) {
  focal_length_ = focal_length;
  baseline_ = baseline;

  // Initialize state for depth estimation (depth, depth_rate, depth_acceleration)
  state_ = Eigen::VectorXd::Zero(3);
  state_(0) = 1.0;  // Initial depth estimate
  covariance_ = Eigen::MatrixXd::Identity(3, 3);

  initialized_ = true;
  ROS_INFO("Depth estimator initialized: focal_length=%.1f, baseline=%.3f",
           focal_length_, baseline_);
}

double DepthEstimator::estimateDepth(const Eigen::Vector2d& feature_point,
                                     const Eigen::Vector2d& feature_velocity,
                                     const Eigen::Vector3d& camera_velocity) {
  // Depth estimation from image motion (Structure from Motion approach)
  // Based on the relationship: Z_dot/Z = -v_z/Z + (u*v_x - v*v_y)/f

  if (!initialized_) {
    initialize(focal_length_, baseline_);
  }

  // Normalize image coordinates
  double u = (feature_point.x() - 320.0) / focal_length_;
  double v = (feature_point.y() - 240.0) / focal_length_;

  // Image velocities
  double u_dot = feature_velocity.x();
  double v_dot = feature_velocity.y();

  // If we have camera velocity, use it for better depth estimation
  double depth_estimate = last_depth_;

  if (camera_velocity.norm() > 0.01) {
    // Use camera motion for depth estimation
    // Simplified model: Z = f * v_x / u_dot (for lateral motion)
    if (std::abs(u_dot) > 0.1) {
      depth_estimate = focal_length_ * camera_velocity.x() / u_dot;
    }
  } else {
    // Use constant velocity model if no camera motion
    // Assume target is at a reasonable distance
    if (std::abs(u_dot) > 0.1 || std::abs(v_dot) > 0.1) {
      // Estimate based on image motion magnitude
      double motion_magnitude = std::sqrt(u_dot * u_dot + v_dot * v_dot);
      depth_estimate = focal_length_ / (motion_magnitude + 1e-6);
    }
  }

  // Clamp depth to reasonable range
  depth_estimate = std::max(0.5, std::min(10.0, depth_estimate));

  // Update state
  state_(0) = depth_estimate;
  last_depth_ = depth_estimate;

  return depth_estimate;
}

bool DepthEstimator::estimateDepthFromStereo(const Eigen::Vector2d& left_point,
                                             const Eigen::Vector2d& right_point,
                                             double& depth) {
  // Stereo depth estimation using disparity
  // Z = (f * baseline) / disparity

  double disparity = std::abs(left_point.x() - right_point.x());

  if (disparity < 1.0) {
    ROS_WARN("Disparity too small for reliable depth estimation: %.2f", disparity);
    return false;
  }

  depth = (focal_length_ * baseline_) / disparity;

  // Clamp to reasonable range
  depth = std::max(0.5, std::min(10.0, depth));

  return true;
}

void DepthEstimator::setFocalLength(double focal_length) {
  focal_length_ = focal_length;
}

void DepthEstimator::setBaseline(double baseline) {
  baseline_ = baseline;
}

double DepthEstimator::getLastDepthEstimate() const {
  return last_depth_;
}

} // namespace target_detection
