#ifndef IBVS_CORE_MATH_UTILS_H
#define IBVS_CORE_MATH_UTILS_H

#include <Eigen/Dense>
#include <vector>

namespace ibvs_core {

class MathUtils {
public:
  // Compute skew-symmetric matrix
  static Eigen::Matrix3d skewSymmetric(const Eigen::Vector3d& v);

  // Compute rotation matrix from Euler angles (roll, pitch, yaw)
  static Eigen::Matrix3d eulerToRotation(double roll, double pitch, double yaw);

  // Compute Euler angles from rotation matrix
  static Eigen::Vector3d rotationToEuler(const Eigen::Matrix3d& R);

  // Compute quaternion from rotation matrix
  static Eigen::Quaterniond rotationToQuaternion(const Eigen::Matrix3d& R);

  // Saturate value within limits
  static double saturate(double value, double min_val, double max_val);

  // Saturate vector within limits
  static Eigen::VectorXd saturate(const Eigen::VectorXd& vec, double max_norm);

  // Compute pseudo-inverse of a matrix
  static Eigen::MatrixXd pseudoInverse(const Eigen::MatrixXd& matrix, double tolerance = 1e-6);

  // TODO: Implement mathematical utility functions
};

} // namespace ibvs_core

#endif // IBVS_CORE_MATH_UTILS_H
