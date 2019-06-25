/**
 *
 *
 * A class solving wavehands_stop functional
 *
 *
 * */
#include "include/wavehands_stop.h"

namespace perception {

void WaveHandsStop::image_callback() {
  // do human pose detection then get the final output info

}

void WaveHandsStop::Run() {
  ros::NodeHandle private_nh("~");
  std::string image_topic_src;

  private_nh.param<std::string>("camera_info_src", 
  image_topic_src, "/cti/sensor/images/");
  image_subscriber_ = private_nh.subscribe(camera_info_src, 1, &WaveHandsStop::image_callback, this);

  // design message to contains stop signals {is_wavehands_stop: true, wavehands_num: 3}
  stop_signal_publisher_ = node_handle_.advertise<autoware_msgs::DetectedObjectArray>(
    "/detection/image_tracker/objects", 1);
  ros::spin();
  ROS_INFO("WaveHandsStop start to run");
}

}  // namespace perception