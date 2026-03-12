#ifndef TARGET_DETECTION_KALMAN_FILTER_H
#define TARGET_DETECTION_KALMAN_FILTER_H

#include <Eigen/Dense>

namespace target_detection {

/**
 * @brief Dual Kalman Filter for target state estimation
 *
 * This implements a dual Kalman filter approach:
 * - One filter for image plane coordinates (u, v)
 * - One filter for depth estimation
 */
class DualKalmanFilter {
public:
  DualKalmanFilter();
  ~DualKalmanFilter();

  /**
   * @brief Initialize the filter with measurement noise parameters
   */
  void initialize(double process_variance, double measurement_variance, double dt);

  /**
   * @brief Update filter with new measurement
   * @param measurement 2D measurement in image plane [u, v]
   * @return Filtered state [u, v, u_dot, v_dot]
   */
  Eigen::Vector4d updateImagePlane(const Eigen::Vector2d& measurement);

  /**
   * @brief Update depth filter with new measurement
   * @param depth_measurement Measured depth
   * @return Filtered depth and depth rate [Z, Z_dot]
   */
  Eigen::Vector2d updateDepth(double depth_measurement);

  /**
   * @brief Get current image plane state estimate
   */
  Eigen::Vector4d getImagePlaneState() const { return state_image_; }

  /**
   * @brief Get current depth state estimate
   */
  Eigen::Vector2d getDepthState() const { return state_depth_; }

  /**
   * @brief Reset the filter
   */
  void reset();

  /**
   * @brief Check if filter is initialized
   */
  bool isInitialized() const { return initialized_; }

private:
  // Image plane filter (4D state: u, v, u_dot, v_dot)
  Eigen::Vector4d state_image_;
  Eigen::Matrix4d P_image_;  // Covariance matrix
  Eigen::Matrix4d Q_image_;  // Process noise
  Eigen::Matrix2d R_image_;  // Measurement noise

  // Depth filter (2D state: Z, Z_dot)
  Eigen::Vector2d state_depth_;
  Eigen::Matrix2d P_depth_;  // Covariance matrix
  Eigen::Matrix2d Q_depth_;  // Process noise
  double R_depth_;           // Measurement noise

  double dt_;  // Time step
  bool initialized_;

  // State transition matrices
  Eigen::Matrix4d F_image_;
  Eigen::Matrix2d F_depth_;

  // Measurement matrices
  Eigen::Matrix<double, 2, 4> H_image_;
  Eigen::Matrix<double, 1, 2> H_depth_;
};

} // namespace target_detection

#endif // TARGET_DETECTION_KALMAN_FILTER_H
