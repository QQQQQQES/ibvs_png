#ifndef TARGET_DETECTION_DEPTH_ESTIMATOR_H
#define TARGET_DETECTION_DEPTH_ESTIMATOR_H

#include <Eigen/Dense>
#include <vector>

namespace target_detection {

class DepthEstimator {
public:
  DepthEstimator();
  ~DepthEstimator();

  void initialize(double focal_length, double baseline);

  double estimateDepth(const Eigen::Vector2d& feature_point,
                       const Eigen::Vector2d& feature_velocity,
                       const Eigen::Vector3d& camera_velocity);

  bool estimateDepthFromStereo(const Eigen::Vector2d& left_point,
                               const Eigen::Vector2d& right_point,
                               double& depth);

  void setFocalLength(double focal_length);
  void setBaseline(double baseline);
  double getLastDepthEstimate() const;

private:
  double focal_length_;
  double baseline_;
  bool initialized_;
  double last_depth_;

  // Kalman filter for depth estimation
  Eigen::VectorXd state_;
  Eigen::MatrixXd covariance_;

  // TODO: Implement depth estimation algorithm
};

} // namespace target_detection

#endif // TARGET_DETECTION_DEPTH_ESTIMATOR_H
