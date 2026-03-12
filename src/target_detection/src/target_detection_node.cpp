#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include "target_detection/target_detector.h"
#include "target_detection/feature_tracker.h"
#include "target_detection/depth_estimator.h"
#include "target_detection/kalman_filter.h"
#include <ibvs_msgs/TargetState.h>
#include <geometry_msgs/Vector3.h>

class TargetDetectionNode {
public:
  TargetDetectionNode() : nh_("~"), it_(nh_) {
    // Initialize components
    detector_ = std::make_shared<target_detection::TargetDetector>();
    tracker_ = std::make_shared<target_detection::FeatureTracker>();
    depth_estimator_ = std::make_shared<target_detection::DepthEstimator>();
    kalman_filter_ = std::make_shared<target_detection::DualKalmanFilter>();

    // Load parameters
    loadParameters();

    // Initialize detector
    detector_->initialize(nh_);

    // Initialize Kalman filter
    kalman_filter_->initialize(process_variance_, measurement_variance_, 1.0/update_rate_);

    // Initialize publishers and subscribers
    std::string image_topic;
    nh_.param<std::string>("image_topic", image_topic, "/iris_0/realsense/depth_camera/color/image_raw");

    image_sub_ = it_.subscribe(image_topic, 1,
                               &TargetDetectionNode::imageCallback, this);
    target_state_pub_ = nh_.advertise<ibvs_msgs::TargetState>("/target_state", 10);
    error_pub_ = nh_.advertise<geometry_msgs::Vector3>("/target_error", 10);

    // Optional: publish debug image
    if (enable_debug_image_) {
      debug_image_pub_ = it_.advertise("/target_detection/debug_image", 1);
    }

    ROS_INFO("Target detection node initialized");
    ROS_INFO("Subscribing to: %s", image_topic.c_str());
  }

private:
  void loadParameters() {
    nh_.param("update_rate", update_rate_, 30.0);
    nh_.param("process_variance", process_variance_, 1e-4);
    nh_.param("measurement_variance", measurement_variance_, 5e-2);
    nh_.param("enable_debug_image", enable_debug_image_, true);
    nh_.param("image_center_u", image_center_u_, 320.0);
    nh_.param("image_center_v", image_center_v_, 240.0);
    nh_.param("focal_length", focal_length_, 500.0);
    nh_.param("use_depth_estimation", use_depth_estimation_, true);

    ROS_INFO("Parameters loaded: update_rate=%.1f Hz, process_var=%.2e, meas_var=%.2e",
             update_rate_, process_variance_, measurement_variance_);
  }

  void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    // Convert ROS image to OpenCV format
    cv_bridge::CvImagePtr cv_ptr;
    try {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // Detect target in image
    ibvs_msgs::TargetState target_state;
    target_state.header = msg->header;

    if (detector_->detectTarget(cv_ptr->image, target_state)) {
      // Apply Dual Kalman Filter for smoothing
      Eigen::Vector2d measurement(target_state.u, target_state.v);
      Eigen::Vector4d filtered_state = kalman_filter_->updateImagePlane(measurement);

      // Update target state with filtered values
      target_state.u = filtered_state(0);
      target_state.v = filtered_state(1);
      target_state.u_dot = filtered_state(2);
      target_state.v_dot = filtered_state(3);

      // Estimate depth if enabled
      if (use_depth_estimation_) {
        double estimated_depth = depth_estimator_->estimateDepth(
            Eigen::Vector2d(target_state.u, target_state.v),
            Eigen::Vector2d(target_state.u_dot, target_state.v_dot),
            Eigen::Vector3d::Zero()  // Camera velocity (should come from odometry)
        );

        // Apply depth Kalman filter
        Eigen::Vector2d depth_state = kalman_filter_->updateDepth(estimated_depth);
        target_state.depth = depth_state(0);
      }

      // Calculate error from image center
      double err_x = target_state.u - image_center_u_;
      double err_y = target_state.v - image_center_v_;

      // Publish target state
      target_state_pub_.publish(target_state);

      // Publish error
      geometry_msgs::Vector3 error_msg;
      error_msg.x = err_x;
      error_msg.y = err_y;
      error_msg.z = 0.0;
      error_pub_.publish(error_msg);

      ROS_DEBUG("Target detected: u=%.1f, v=%.1f, u_dot=%.2f, v_dot=%.2f, depth=%.2f",
                target_state.u, target_state.v, target_state.u_dot,
                target_state.v_dot, target_state.depth);

      // Publish debug image if enabled
      if (enable_debug_image_) {
        publishDebugImage(cv_ptr->image, target_state, err_x, err_y);
      }
    } else {
      ROS_DEBUG_THROTTLE(1.0, "Target not detected");
    }
  }

  void publishDebugImage(const cv::Mat& image, const ibvs_msgs::TargetState& target_state,
                         double err_x, double err_y) {
    cv::Mat debug_img = image.clone();

    // Draw target position
    cv::circle(debug_img, cv::Point(target_state.u, target_state.v),
               5, cv::Scalar(0, 255, 0), -1);

    // Draw image center
    cv::circle(debug_img, cv::Point(image_center_u_, image_center_v_),
               3, cv::Scalar(255, 0, 0), -1);

    // Draw error line
    cv::line(debug_img,
             cv::Point(image_center_u_, image_center_v_),
             cv::Point(target_state.u, target_state.v),
             cv::Scalar(0, 0, 255), 2);

    // Add text information
    std::string info = cv::format("Error: (%.1f, %.1f)", err_x, err_y);
    cv::putText(debug_img, info, cv::Point(10, 30),
                cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);

    // Publish debug image
    sensor_msgs::ImagePtr debug_msg = cv_bridge::CvImage(
        std_msgs::Header(), "bgr8", debug_img).toImageMsg();
    debug_image_pub_.publish(debug_msg);
  }

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher debug_image_pub_;
  ros::Publisher target_state_pub_;
  ros::Publisher error_pub_;

  std::shared_ptr<target_detection::TargetDetector> detector_;
  std::shared_ptr<target_detection::FeatureTracker> tracker_;
  std::shared_ptr<target_detection::DepthEstimator> depth_estimator_;
  std::shared_ptr<target_detection::DualKalmanFilter> kalman_filter_;

  // Parameters
  double update_rate_;
  double process_variance_;
  double measurement_variance_;
  bool enable_debug_image_;
  double image_center_u_;
  double image_center_v_;
  double focal_length_;
  bool use_depth_estimation_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "target_detection_node");
  TargetDetectionNode node;
  ros::spin();
  return 0;
}
