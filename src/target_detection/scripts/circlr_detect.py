import rospy
import cv2
import numpy as np
from sensor_msgs.msg import Image
from cv_bridge import CvBridge  # 关键工具：将ROS图片转为OpenCV图片
from geometry_msgs.msg import Vector3

class KalmanFilter1D:
    """简单的1D卡尔曼滤波器，用于平滑位置测量"""
    def __init__(self, process_variance=1e-5, measurement_variance=1e-2):
        self.x = 0.0  # 状态估计（位置）
        self.v = 0.0  # 速度估计
        self.P = np.array([[1.0, 0.0], [0.0, 1.0]])  # 协方差矩阵
        self.Q = np.array([[process_variance, 0], [0, process_variance]])  # 过程噪声
        self.R = measurement_variance  # 测量噪声
        self.dt = 0.033  # 假设30Hz
        self.initialized = False

    def update(self, measurement):
        if not self.initialized:
            self.x = measurement
            self.initialized = True
            return self.x

        # 预测
        F = np.array([[1.0, self.dt], [0.0, 1.0]])  # 状态转移矩阵
        x_pred = F @ np.array([self.x, self.v])
        P_pred = F @ self.P @ F.T + self.Q

        # 更新
        H = np.array([1.0, 0.0])  # 测量矩阵
        y = measurement - H @ x_pred  # 残差
        S = H @ P_pred @ H.T + self.R  # 残差协方差
        K = P_pred @ H.T / S  # 卡尔曼增益

        x_new = x_pred + K * y
        self.P = (np.eye(2) - np.outer(K, H)) @ P_pred

        self.x = x_new[0]
        self.v = x_new[1]

        return self.x

class GazeboObjectDetector:
    def __init__(self):
        rospy.init_node('gazebo_object_detector')
        self.bridge = CvBridge()

        # 1. 订阅 Gazebo 机器人的摄像头话题 (根据你的模型修改话题名)
        self.image_sub = rospy.Subscriber("/iris_0/realsense/depth_camera/color/image_raw", Image, self.image_callback)

        # 2. 发布误差数据
        self.error_pub = rospy.Publisher('error', Vector3, queue_size=1)

        self.low_range = np.array([0, 123, 100])        # 红色 HSV 阈值 (可以沿用你 AirSim 的参数，但 Gazebo 光照不同可能需要微调)
        self.high_range = np.array([5, 255, 255])

        # 卡尔曼滤波器（分别用于 x 和 y 方向）
        # process_variance 越小越信任模型，measurement_variance 越小越信任测量
        self.kf_x = KalmanFilter1D(process_variance=1e-4, measurement_variance=5e-2)
        self.kf_y = KalmanFilter1D(process_variance=1e-4, measurement_variance=5e-2)

    def image_callback(self, data):
        # 将 ROS 图像消息转换为 OpenCV 格式
        cv_img = self.bridge.imgmsg_to_cv2(data, "bgr8")
        
        # 图像处理逻辑 (保持不变)
        hsv = cv2.cvtColor(cv_img, cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv, self.low_range, self.high_range)
        mask = cv2.dilate(mask, None, iterations=2)
        
        # 计算质心
        M = cv2.moments(mask)
        if M["m00"] > 0:
            cX = int(M["m10"] / M["m00"])
            cY = int(M["m01"] / M["m00"])
            
            # 计算偏差值 (相对于屏幕中心)
            height, width = cv_img.shape[:2]
            err_x_raw = cX  - width/2
            err_y_raw = cY  - height/2

            # 卡尔曼滤波平滑
            err_x = self.kf_x.update(err_x_raw)
            err_y = self.kf_y.update(err_y_raw)

            rospy.loginfo("Raw: [%.1f, %.1f] -> Filtered: [%.2f, %.2f]",
                         err_x_raw, err_y_raw, err_x, err_y)
            self.error_pub.publish(Vector3(err_x, err_y, 0))
            
            # 可视化调试
            cv2.circle(cv_img, (cX, cY), 5, (0, 255, 0), -1)
            cv2.imshow("Gazebo Tracking", cv_img)
            cv2.waitKey(1)
        else:
            rospy.logwarn("Target not found in Gazebo!")

if __name__ == '__main__':
    detector = GazeboObjectDetector()
    rospy.spin()