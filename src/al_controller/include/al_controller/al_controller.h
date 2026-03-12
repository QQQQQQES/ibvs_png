#ifndef AL_CONTROLLER_AL_CONTROLLER_H
#define AL_CONTROLLER_AL_CONTROLLER_H

#include <ros/ros.h>
#include <Eigen/Dense>
#include <geometry_msgs/Vector3.h>

namespace al_controller {

/**
 * @brief AL (Acceleration and angular velocity to Lift and angular velocity) Controller
 *
 * 实现论文公式(17)-(23):
 * - 公式(17): 推力向量 = 期望加速度 - 重力
 * - 公式(18): 期望推力方向 n_fd
 * - 公式(19): Rodrigues旋转公式计算姿态旋转
 * - 公式(20-21): 期望旋转矩阵 R_d
 * - 公式(22-23): 期望角速度 omega_d
 */
class ALController {
public:
  struct AttitudeCommand {
    Eigen::Vector3d n_fd;       // 期望升力方向 (formula 18)
    double thrust;              // 归一化推力 [0, 1]
    Eigen::Vector3d omega_d;    // 期望角速度 (formula 22-23)
  };

  ALController();
  ~ALController();

  bool initialize(const ros::NodeHandle& nh);

  /**
   * @brief 计算期望姿态指令 (公式17-23)
   * @param a_d 期望加速度 (m/s²)
   * @param R_b_e 当前无人机姿态旋转矩阵 (Body->ENU)
   * @return 姿态指令 (推力方向, 推力大小, 角速度)
   */
  AttitudeCommand computeAttitudeCommand(const Eigen::Vector3d& a_d,
                                         const Eigen::Matrix3d& R_b_e);

  /**
   * @brief 更新无人机姿态
   * @param orientation 当前姿态四元数
   */
  void updateUAVOrientation(const Eigen::Quaterniond& orientation);

  /**
   * @brief 设置推力映射系数
   * @param thr2acc 推力到加速度的映射系数
   */
  void setThr2Acc(double thr2acc);

  /**
   * @brief 获取当前推力映射系数
   */
  double getThr2Acc() const;

  /**
   * @brief 获取当前旋转矩阵
   */
  Eigen::Matrix3d getRotationMatrix() const;

private:
  /**
   * @brief 计算姿态旋转矩阵 (公式19: Rodrigues旋转公式)
   * @param n_fd 期望推力方向
   * @return 旋转矩阵 R_tilt
   */
  Eigen::Matrix3d computeAttitudeRotation(const Eigen::Vector3d& n_fd);

  /**
   * @brief 计算期望角速度 (公式22-23)
   * @param R_d 期望旋转矩阵
   * @param R_b_e 当前旋转矩阵
   * @return 期望角速度 omega_d
   */
  Eigen::Vector3d computeAngularVelocity(const Eigen::Matrix3d& R_d,
                                         const Eigen::Matrix3d& R_b_e);

  /**
   * @brief 计算反对称矩阵
   * @param v 三维向量
   * @return 反对称矩阵 [v]_×
   */
  Eigen::Matrix3d skewSymmetric(const Eigen::Vector3d& v);

  /**
   * @brief 限制值在指定范围内
   */
  double clamp(double value, double min_val, double max_val);

  // 参数
  double thr2acc_;           // 推力到加速度映射系数
  double thrust_min_;        // 最小推力
  double thrust_max_;        // 最大推力
  double max_thrust_acc_;    // 最大推力加速度 (m/s²)

  // 常量
  static constexpr double GRAVITY = 9.8;  // 重力加速度 (m/s²)

  // 状态
  Eigen::Quaterniond uav_orientation_;
  Eigen::Matrix3d R_b_e_;    // 当前姿态旋转矩阵
};

} // namespace al_controller

#endif // AL_CONTROLLER_AL_CONTROLLER_H
