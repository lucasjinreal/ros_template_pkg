/**
 *
 *
 * A class solving wavehands_stop functional
 *
 *
 * */

#include <sensor_msgs/Image.h>
#include "wavehands_stop.h"


namespace perception {


void WaveHandsStop::image_callback(const sensor_msgs::ImageConstPtr &msg) {
  // do human pose detection then get the final output info
  // call estimator here to get poses

  // the detection poses will get all poses, iter
  // them if there anyone waving hands
  // if have, then publish a topic out indicates
  // there is someone wave hands

  // get cv image, apply estimate
  cv_bridge::CvImagePtr cv_ptr;
  cv_ptr = cv_bridge::toCvCopy(msg);
  crt_image = cv_ptr->image;

  // now we get
  std::vector<HumanPose> poses = pHumanPoseEstimator->estimate(crt_image);
  // poses got, render it to debug
  // iter poses to check if anyone wavehand

  cti_msgs::HumanGestureControl ges_ctl_msg;
  ges_ctl_msg.header = msg->header;
  for (int j = 0; j < poses.size(); ++j) {
	if (poses[j].pose_type == 1) {
	  // publish a message indicates someone wavehands
	  ges_ctl_msg.has_wave_hands_stop = true;
	}
  }
  if (is_debug) {
	// render poses on image and show it out
	renderHumanPose(poses, crt_image);
	cv::imshow("res", crt_image);
	cv::waitKey(1);
  }
  // publish the msg
  stop_signal_publisher_.publish(ges_ctl_msg);
}

void WaveHandsStop::Run() {
  ros::NodeHandle private_nh("~");
  std::string image_topic_src;
  std::string pub_wavehands_topic_src;
  std::string model_path;

  private_nh.param<std::string>("model_path",
								model_path, "~/dl_models/human-pose.pth");
  private_nh.param<std::string>("image_topic_src",
								image_topic_src, "/cti/sensor/images/");
  private_nh.param<std::string>("pub_topic_src",
								pub_wavehands_topic_src, "/cti/perception/wavehands_stop_signal");
  private_nh.param("is_debug", is_debug, false);

  image_subscriber_ = private_nh.subscribe(image_topic_src, 1, &perception::WaveHandsStop::image_callback, this);
  // design message to contains stop signals {is_wavehands_stop: true, wavehands_num: 3}
  stop_signal_publisher_ = node_handle_.advertise<cti_msgs::HumanGestureControl>(pub_wavehands_topic_src, 10);

  LOG(google::INFO) << "loading human pose estimate model from: " << model_path;
  LOG(google::INFO) << "image_topic_src						  : " << image_topic_src;
  pHumanPoseEstimator = make_shared<HumanPoseEstimator>(model_path);
  LOG(google::INFO) << __APP_NAME__ << " is up. debug mode: " << is_debug;

  ros::spin();
}


}  // namespace perception