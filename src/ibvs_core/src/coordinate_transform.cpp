#include "ibvs_core/coordinate_transform.h"

namespace ibvs_core {

Eigen::Vector3d CoordinateTransform::cameraToBody(const Eigen::Vector3d& point_camera) {
  // TODO: Implement camera to body frame transformation
  return point_camera;
}

Eigen::Vector3d CoordinateTransform::bodyToWorld(const Eigen::Vector3d& point_body,
                                                 const Eigen::Quaterniond& orientation) {
  // TODO: Implement body to world frame transformation
  return orientation * point_body;
}

Eigen::Vector3d CoordinateTransform::worldToBody(const Eigen::Vector3d& point_world,
                                                 const Eigen::Quaterniond& orientation) {
  // TODO: Implement world to body frame transformation
  return orientation.inverse() * point_world;
}

Eigen::Vector2d CoordinateTransform::imageToNormalized(const Eigen::Vector2d& image_point,
                                                       double focal_length,
                                                       const Eigen::Vector2d& principal_point) {
  // TODO: Implement image to normalized coordinates transformation
  Eigen::Vector2d normalized;
  normalized.x() = (image_point.x() - principal_point.x()) / focal_length;
  normalized.y() = (image_point.y() - principal_point.y()) / focal_length;
  return normalized;
}

Eigen::Vector2d CoordinateTransform::normalizedToImage(const Eigen::Vector2d& normalized_point,
                                                       double focal_length,
                                                       const Eigen::Vector2d& principal_point) {
  // TODO: Implement normalized to image coordinates transformation
  Eigen::Vector2d image;
  image.x() = normalized_point.x() * focal_length + principal_point.x();
  image.y() = normalized_point.y() * focal_length + principal_point.y();
  return image;
}

} // namespace ibvs_core
