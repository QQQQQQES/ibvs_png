#ifndef TARGET_DETECTION_TARGET_DETECTOR_H
#define TARGET_DETECTION_TARGET_DETECTOR_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>
#include <opencv2/opencv.hpp>
#include <ibvs_msgs/TargetState.h>

namespace target_detection {

class TargetDetector {
public:
  TargetDetector();
  ~TargetDetector();

  bool initialize(const ros::NodeHandle& nh);

  bool detectTarget(const cv::Mat& image, ibvs_msgs::TargetState& target_state);

  void setDetectionParameters(double threshold, int min_area);

  void setHSVRange(const cv::Scalar& low, const cv::Scalar& high);

private:
  // Detection parameters
  double detection_threshold_;
  int min_detection_area_;
  int dilation_iterations_;

  // HSV color range for target detection
  cv::Scalar hsv_low_range_;
  cv::Scalar hsv_high_range_;

  // Last detection info for velocity estimation
  ros::Time last_detection_time_;
  cv::Point2f last_centroid_;

  // Image processing methods
  cv::Mat preprocessImage(const cv::Mat& image);
  std::vector<cv::Point2f> extractFeatures(const cv::Mat& image);
};

} // namespace target_detection

#endif // TARGET_DETECTION_TARGET_DETECTOR_H
