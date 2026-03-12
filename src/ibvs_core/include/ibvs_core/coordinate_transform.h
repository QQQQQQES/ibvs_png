#ifndef IBVS_CORE_COORDINATE_TRANSFORM_H
#define IBVS_CORE_COORDINATE_TRANSFORM_H

#include <Eigen/Dense>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3.h>

namespace ibvs_core {

class CoordinateTransform {
public:
  // Transform from camera frame to body frame
  static Eigen::Vector3d cameraToBody(const Eigen::Vector3d& point_camera);

  // Transform from body frame to world frame
  static Eigen::Vector3d bodyToWorld(const Eigen::Vector3d& point_body,
                                     const Eigen::Quaterniond& orientation);

  // Transform from world frame to body frame
  static Eigen::Vector3d worldToBody(const Eigen::Vector3d& point_world,
                                     const Eigen::Quaterniond& orientation);

  // Convert image coordinates to normalized camera coordinates
  static Eigen::Vector2d imageToNormalized(const Eigen::Vector2d& image_point,
                                          double focal_length,
                                          const Eigen::Vector2d& principal_point);

  // Convert normalized camera coordinates to image coordinates
  static Eigen::Vector2d normalizedToImage(const Eigen::Vector2d& normalized_point,
                                          double focal_length,
                                          const Eigen::Vector2d& principal_point);

  // TODO: Implement coordinate transformation functions
};

} // namespace ibvs_core

#endif // IBVS_CORE_COORDINATE_TRANSFORM_H
