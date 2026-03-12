#include "target_detection/target_detector.h"
#include <ros/ros.h>

namespace target_detection {

TargetDetector::TargetDetector()
  : detection_threshold_(0.5),
    min_detection_area_(100) {

  // Default HSV range for red color detection (similar to circle_detect.py)
  hsv_low_range_ = cv::Scalar(0, 123, 100);
  hsv_high_range_ = cv::Scalar(5, 255, 255);
}

TargetDetector::~TargetDetector() {
}

bool TargetDetector::initialize(const ros::NodeHandle& nh) {
  // Load HSV threshold parameters
  std::vector<int> low_range, high_range;
  if (nh.getParam("hsv_low_range", low_range) && low_range.size() == 3) {
    hsv_low_range_ = cv::Scalar(low_range[0], low_range[1], low_range[2]);
  }
  if (nh.getParam("hsv_high_range", high_range) && high_range.size() == 3) {
    hsv_high_range_ = cv::Scalar(high_range[0], high_range[1], high_range[2]);
  }

  nh.param("min_detection_area", min_detection_area_, 100);
  nh.param("dilation_iterations", dilation_iterations_, 2);

  ROS_INFO("Target detector initialized with HSV range: [%d,%d,%d] to [%d,%d,%d]",
           (int)hsv_low_range_[0], (int)hsv_low_range_[1], (int)hsv_low_range_[2],
           (int)hsv_high_range_[0], (int)hsv_high_range_[1], (int)hsv_high_range_[2]);

  return true;
}

bool TargetDetector::detectTarget(const cv::Mat& image, ibvs_msgs::TargetState& target_state) {
  if (image.empty()) {
    ROS_WARN("Empty image received");
    return false;
  }

  // Convert to HSV color space
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Apply color threshold to create binary mask
  cv::Mat mask;
  cv::inRange(hsv, hsv_low_range_, hsv_high_range_, mask);

  // Morphological operations to reduce noise
  cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), dilation_iterations_);

  // Calculate moments to find centroid
  cv::Moments M = cv::moments(mask);

  if (M.m00 > min_detection_area_) {
    // Calculate centroid position
    double cX = M.m10 / M.m00;
    double cY = M.m01 / M.m00;

    // Fill target state message
    target_state.u = cX;
    target_state.v = cY;
    target_state.confidence = std::min(1.0, M.m00 / 10000.0);  // Normalize confidence

    // Store last detection for velocity estimation
    last_detection_time_ = ros::Time::now();
    last_centroid_ = cv::Point2f(cX, cY);

    ROS_DEBUG("Target detected at (%.1f, %.1f) with confidence %.2f",
              cX, cY, target_state.confidence);

    return true;
  } else {
    ROS_DEBUG("Target not found (area too small: %.0f < %d)", M.m00, min_detection_area_);
    return false;
  }
}

void TargetDetector::setDetectionParameters(double threshold, int min_area) {
  detection_threshold_ = threshold;
  min_detection_area_ = min_area;
}

void TargetDetector::setHSVRange(const cv::Scalar& low, const cv::Scalar& high) {
  hsv_low_range_ = low;
  hsv_high_range_ = high;
}

cv::Mat TargetDetector::preprocessImage(const cv::Mat& image) {
  cv::Mat processed = image.clone();

  // Optional: Apply Gaussian blur to reduce noise
  cv::GaussianBlur(processed, processed, cv::Size(5, 5), 0);

  return processed;
}

std::vector<cv::Point2f> TargetDetector::extractFeatures(const cv::Mat& image) {
  std::vector<cv::Point2f> features;

  // Use goodFeaturesToTrack for corner detection
  cv::goodFeaturesToTrack(image, features, 100, 0.01, 10);

  return features;
}

} // namespace target_detection
