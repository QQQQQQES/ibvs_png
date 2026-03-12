#include "ibvs_core/math_utils.h"
#include <cmath>

namespace ibvs_core {

Eigen::Matrix3d MathUtils::skewSymmetric(const Eigen::Vector3d& v) {
  Eigen::Matrix3d skew;
  skew << 0, -v.z(), v.y(),
          v.z(), 0, -v.x(),
          -v.y(), v.x(), 0;
  return skew;
}

Eigen::Matrix3d MathUtils::eulerToRotation(double roll, double pitch, double yaw) {
  // TODO: Implement Euler to rotation matrix conversion
  Eigen::Matrix3d R = Eigen::Matrix3d::Identity();
  return R;
}

Eigen::Vector3d MathUtils::rotationToEuler(const Eigen::Matrix3d& R) {
  // TODO: Implement rotation matrix to Euler angles conversion
  Eigen::Vector3d euler = Eigen::Vector3d::Zero();
  return euler;
}

Eigen::Quaterniond MathUtils::rotationToQuaternion(const Eigen::Matrix3d& R) {
  // TODO: Implement rotation matrix to quaternion conversion
  return Eigen::Quaterniond(R);
}

double MathUtils::saturate(double value, double min_val, double max_val) {
  return std::max(min_val, std::min(max_val, value));
}

Eigen::VectorXd MathUtils::saturate(const Eigen::VectorXd& vec, double max_norm) {
  double norm = vec.norm();
  if (norm > max_norm) {
    return vec * (max_norm / norm);
  }
  return vec;
}

Eigen::MatrixXd MathUtils::pseudoInverse(const Eigen::MatrixXd& matrix, double tolerance) {
  // TODO: Implement pseudo-inverse computation using SVD
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(matrix, Eigen::ComputeFullU | Eigen::ComputeFullV);
  return svd.solve(Eigen::MatrixXd::Identity(matrix.rows(), matrix.rows()));
}

} // namespace ibvs_core
