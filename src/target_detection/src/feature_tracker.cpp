#include "target_detection/feature_tracker.h"

namespace target_detection {

FeatureTracker::FeatureTracker()
  : max_features_(100),
    quality_level_(0.01) {
}

FeatureTracker::~FeatureTracker() {
}

void FeatureTracker::initialize(int max_features, double quality_level) {
  max_features_ = max_features;
  quality_level_ = quality_level;
}

bool FeatureTracker::trackFeatures(const cv::Mat& prev_image, const cv::Mat& curr_image,
                                   std::vector<cv::Point2f>& tracked_points,
                                   std::vector<cv::Point2f>& velocities) {
  // TODO: Implement optical flow tracking
  return false;
}

void FeatureTracker::reset() {
  image_buffer_.clear();
  feature_buffer_.clear();
}

} // namespace target_detection
