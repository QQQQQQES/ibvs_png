#ifndef TARGET_DETECTION_FEATURE_TRACKER_H
#define TARGET_DETECTION_FEATURE_TRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <deque>

namespace target_detection {

class FeatureTracker {
public:
  FeatureTracker();
  ~FeatureTracker();

  void initialize(int max_features, double quality_level);

  bool trackFeatures(const cv::Mat& prev_image, const cv::Mat& curr_image,
                     std::vector<cv::Point2f>& tracked_points,
                     std::vector<cv::Point2f>& velocities);

  void reset();

private:
  int max_features_;
  double quality_level_;

  std::deque<cv::Mat> image_buffer_;
  std::deque<std::vector<cv::Point2f>> feature_buffer_;

  // TODO: Implement optical flow tracking
};

} // namespace target_detection

#endif // TARGET_DETECTION_FEATURE_TRACKER_H
