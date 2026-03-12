检测参数 (detection)

threshold: 0.5 - 检测阈值，越小越敏感（范围 0-1）
min_area: 100 - 最小目标面积（像素），过滤小噪点
max_area: 10000 - 最大目标面积（像素），过滤过大区域
dilation_iterations: 2 - 膨胀迭代次数，填充目标内部空洞

HSV 颜色范围（红色目标）

hsv_low_range: [0, 123, 100] - HSV 下限 [色调H, 饱和度S, 明度V]
hsv_high_range: [5, 255, 255] - HSV 上限
调整建议：根据实际光照条件调整，可以用 OpenCV 的 HSV 调试工具

卡尔曼滤波器 (kalman_filter)

process_variance: 0.0001 - 过程噪声，越小越信任模型预测
measurement_variance: 0.05 - 测量噪声，越小越信任测量值
update_rate: 30.0 - 更新频率（Hz）

图像参数 (image)

center_u: 320.0 - 图像中心 x 坐标（像素）
center_v: 240.0 - 图像中心 y 坐标（像素）
width: 640 / height: 480 - 图像分辨率

深度估计 (depth_estimation)

focal_length: 500.0 - 相机焦距（像素）
baseline: 0.12 - 双目基线距离（米）
min_depth: 0.5 / max_depth: 10.0 - 深度范围（米）

调试选项 (debug)

enable_debug_image: true - 是否发布可视化图像
log_level: info - 日志级别（debug/info/warn/error）