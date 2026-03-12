#ifndef LOS_CALCULATOR_LOS_CALCULATOR_H
#define LOS_CALCULATOR_LOS_CALCULATOR_H

#include <ros/ros.h>
#include <Eigen/Dense>
#include <ibvs_msgs/TargetState.h>
#include <geometry_msgs/Vector3.h>

namespace los_calculator {

/**
 * @brief LOS (Line-of-Sight) Calculator
 *
 * Computes LOS angles (q_y, q_z), lead angles (sigma_y, sigma_z),
 * and their rates (dq_y_dt, dq_z_dt) from pixel errors.
 *
 * Based on PNG guidance law equations.
 */
class LOSCalculator {
public:
  LOSCalculator();
  ~LOSCalculator();

  bool initialize(const ros::NodeHandle& nh);

  /**
   * @brief Compute LOS rate from pixel error
   * @param err_x Pixel error in x direction
   * @param err_y Pixel error in y direction
   * @return Vector2d containing [dq_y_dt, dq_z_dt]
   */
  Eigen::Vector2d computeLOSRate(double err_x, double err_y);

  /**
   * @brief Get current LOS angles
   * @return Vector2d containing [q_y, q_z]
   */
  Eigen::Vector2d getLOSAngles() const;

  /**
   * @brief Get current lead angles
   * @return Vector2d containing [sigma_y, sigma_z]
   */
  Eigen::Vector2d getLeadAngles() const;

  /**
   * @brief Get target normal vector n_t
   * @return Vector3d containing n_t in camera frame
   */
  Eigen::Vector3d getTargetNormal() const;

  /**
   * @brief Compute desired velocity direction from lead angles
   * @return Vector3d containing n_vd (normalized desired velocity direction)
   */
  Eigen::Vector3d getDesiredVelocityDirection() const;

  /**
   * @brief Update UAV velocity for lead angle computation
   * @param velocity Current UAV velocity
   */
  void updateUAVVelocity(const Eigen::Vector3d& velocity);

  /**
   * @brief Update target velocity for relative motion
   * @param velocity Current target velocity
   */
  void updateTargetVelocity(const Eigen::Vector3d& velocity);

  /**
   * @brief Update UAV orientation for coordinate transformation
   * @param orientation Current UAV orientation (quaternion)
   */
  void updateUAVOrientation(const Eigen::Quaterniond& orientation);

  /**
   * @brief Set PNG gain K
   * @param K PNG navigation constant
   */
  void setPNGGain(double K);

private:
  // Convert pixel error to target normal vector n_t
  Eigen::Vector3d pixelErrorToNormal(double err_x, double err_y);

  // Compute LOS angles and lead angles
  void computeLOSAndLeadAngles(const Eigen::Vector3d& n_t);

  // Wrap angle to [-pi, pi]
  double wrapToPi(double angle);

  // Parameters
  double K_;              // PNG navigation constant
  double v_m_;            // Maximum velocity
  double focal_length_;   // Camera focal length
  double depth_;          // Target depth
  double dt_;             // Time step

  // State variables
  double q_y_;            // LOS angle in horizontal plane (azimuth)
  double q_z_;            // LOS angle in vertical plane (elevation)
  double sigma_y_d;        // Lead angle in horizontal plane
  double sigma_z_d;        // Lead angle in vertical plane
  double delta_q_y_;      // Change in q_y
  double delta_q_z_;      // Change in q_z

  // Previous states
  double prev_q_y_;
  double prev_q_z_;
  double prev_sigma_y_actual_;
  double prev_sigma_z_actual_;

  // Initialization flag
  bool initialized_;

  // Low-pass filter for LOS rate
  double prev_dq_y_dt_;
  double prev_dq_z_dt_;
  double filter_alpha_;  // Filter coefficient (0-1, higher = less filtering)

  // UAV state
  Eigen::Vector3d uav_velocity_;
  Eigen::Vector3d target_velocity_;
  Eigen::Quaterniond uav_orientation_;

  // Target normal vector
  Eigen::Vector3d n_t_;
};

} // namespace los_calculator

#endif // LOS_CALCULATOR_LOS_CALCULATOR_H
