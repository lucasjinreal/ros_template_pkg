#ifndef VISION_BEYOND_TRACK_H
#define VISION_BEYOND_TRACK_H

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <tf/tf.h>
#include <chrono>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "./human_pose_estimator.h"


#define __APP_NAME__ "wavehands_stop"

namespace perception {

class WaveHandsStop {
 private:
  void initialize();

// several subscribers
  ros::Subscriber image_subscriber_;

  ros::Publisher stop_signal_publisher_;
  ros::NodeHandle node_handle_;

    // our private estimator
  HumanPoseEstimator human_pose_estimator_;

 public:
  WaveHandsStop(){};
  ~WaveHandsStop(){};
  void Run();

};
}  // namespace perception

#endif
