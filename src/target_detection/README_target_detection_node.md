# Target Detection Node 说明文档

## 概述

`target_detection_node` 是一个基于ROS的目标检测节点，用于实时检测图像中的目标，并通过卡尔曼滤波器平滑处理目标的位置和速度信息。该节点主要应用于视觉伺服（IBVS）系统中。

## 主要功能

- **目标检测**：从相机图像中实时检测目标位置
- **卡尔曼滤波**：使用双卡尔曼滤波器平滑目标的图像平面坐标和速度
- **深度估计**：可选的深度估计功能，估算目标的深度信息
- **误差计算**：计算目标位置与图像中心的偏差
- **调试可视化**：可选的调试图像发布，显示检测结果和误差信息

## 核心组件

### 1. TargetDetector（目标检测器）
负责在图像中检测目标，返回目标在图像平面的坐标。

### 2. FeatureTracker（特征跟踪器）
用于跟踪图像特征点（当前代码中已初始化但未直接使用）。

### 3. DepthEstimator（深度估计器）
根据目标的图像平面运动和相机速度估算目标深度。

### 4. DualKalmanFilter（双卡尔曼滤波器）
- **图像平面滤波**：平滑目标的 (u, v) 坐标及其速度 (u_dot, v_dot)
- **深度滤波**：平滑估算的深度值

## 参数配置

### ROS参数列表

| 参数名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| `image_topic` | string | `/iris_0/realsense/depth_camera/color/image_raw` | 输入图像话题 |
| `update_rate` | double | 30.0 | 更新频率（Hz） |
| `process_variance` | double | 1e-4 | 卡尔曼滤波器过程噪声方差 |
| `measurement_variance` | double | 5e-2 | 卡尔曼滤波器测量噪声方差 |
| `enable_debug_image` | bool | false | 是否发布调试图像 |
| `image_center_u` | double | 320.0 | 图像中心U坐标（像素） |
| `image_center_v` | double | 240.0 | 图像中心V坐标（像素） |
| `focal_length` | double | 500.0 | 相机焦距（像素） |
| `use_depth_estimation` | bool | true | 是否启用深度估计 |

### 参数配置示例

```yaml
target_detection_node:
  image_topic: "/camera/color/image_raw"
  update_rate: 30.0
  process_variance: 0.0001
  measurement_variance: 0.05
  enable_debug_image: true
  image_center_u: 320.0
  image_center_v: 240.0
  focal_length: 500.0
  use_depth_estimation: true
```

## 话题接口

### 订阅话题

| 话题名 | 消息类型 | 说明 |
|--------|----------|------|
| `<image_topic>` | `sensor_msgs/Image` | 输入的相机图像（BGR8格式） |

### 发布话题

| 话题名 | 消息类型 | 说明 |
|--------|----------|------|
| `/target_state` | `ibvs_msgs/TargetState` | 目标状态信息（位置、速度、深度） |
| `/target_error` | `geometry_msgs/Vector3` | 目标相对于图像中心的误差 |
| `/target_detection/debug_image` | `sensor_msgs/Image` | 调试图像（可选，需启用） |

### TargetState 消息内容

```
header          # 时间戳和坐标系信息
float64 u       # 目标在图像平面的U坐标（像素）
float64 v       # 目标在图像平面的V坐标（像素）
float64 u_dot   # U方向速度（像素/秒）
float64 v_dot   # V方向速度（像素/秒）
float64 depth   # 目标深度（米）
```

### 误差消息内容

```
float64 x       # U方向误差（目标U - 图像中心U）
float64 y       # V方向误差（目标V - 图像中心V）
float64 z       # 保留字段（当前为0）
```

## 工作流程

```
1. 接收图像
   ↓
2. 图像格式转换（ROS → OpenCV）
   ↓
3. 目标检测
   ↓
4. 卡尔曼滤波（图像平面）
   ├─ 输入：测量的 (u, v)
   └─ 输出：滤波后的 (u, v, u_dot, v_dot)
   ↓
5. 深度估计（可选）
   ├─ 根据图像平面运动估算深度
   └─ 卡尔曼滤波（深度）
   ↓
6. 计算误差
   ├─ err_x = u - image_center_u
   └─ err_y = v - image_center_v
   ↓
7. 发布结果
   ├─ 发布目标状态
   ├─ 发布误差信息
   └─ 发布调试图像（可选）
```

## 调试图像说明

当 `enable_debug_image` 设置为 `true` 时，节点会发布包含以下信息的调试图像：

- **绿色圆点**：检测到的目标位置
- **蓝色圆点**：图像中心位置
- **红色直线**：从图像中心到目标的误差向量
- **文本信息**：显示当前的误差值 (err_x, err_y)

## 使用方法

### 1. 编译

```bash
cd ~/桌面/ibvs_png_ws
catkin_make
source devel/setup.bash
```

### 2. 运行节点

```bash
rosrun target_detection target_detection_node
```

### 3. 使用launch文件运行（推荐）

创建 launch 文件：

```xml
<launch>
  <node name="target_detection" pkg="target_detection" type="target_detection_node" output="screen">
    <param name="image_topic" value="/camera/color/image_raw"/>
    <param name="update_rate" value="30.0"/>
    <param name="enable_debug_image" value="true"/>
    <param name="image_center_u" value="320.0"/>
    <param name="image_center_v" value="240.0"/>
  </node>
</launch>
```

运行：

```bash
roslaunch target_detection target_detection.launch
```

### 4. 查看输出

```bash
# 查看目标状态
rostopic echo /target_state

# 查看误差信息
rostopic echo /target_error

# 查看调试图像
rosrun image_view image_view image:=/target_detection/debug_image
```

## 注意事项

1. **图像话题格式**：输入图像必须是 BGR8 格式
2. **相机参数**：需要根据实际相机配置 `image_center_u`、`image_center_v` 和 `focal_length`
3. **滤波器参数调优**：根据实际应用场景调整 `process_variance` 和 `measurement_variance`
4. **深度估计**：深度估计功能需要相机速度信息（当前代码中使用零向量，需要从里程计获取）
5. **性能考虑**：调试图像会增加计算负担，生产环境建议关闭

## 依赖项

- ROS (Kinetic/Melodic/Noetic)
- OpenCV
- cv_bridge
- image_transport
- Eigen3
- 自定义消息包：`ibvs_msgs`

## 相关文件

- 源文件：`src/target_detection_node.cpp`
- 头文件：
  - `include/target_detection/target_detector.h`
  - `include/target_detection/feature_tracker.h`
  - `include/target_detection/depth_estimator.h`
  - `include/target_detection/kalman_filter.h`

## 故障排查

### 问题：无法检测到目标
- 检查图像话题是否正确
- 确认目标检测器参数配置
- 查看调试图像确认图像质量

### 问题：滤波结果抖动
- 增大 `process_variance`
- 减小 `measurement_variance`
- 降低 `update_rate`

### 问题：深度估计不准确
- 确认相机速度信息是否正确
- 检查焦距参数是否匹配实际相机
- 考虑使用深度相机直接获取深度

## 版本信息

- 文档版本：1.0
- 最后更新：2026-03-03
