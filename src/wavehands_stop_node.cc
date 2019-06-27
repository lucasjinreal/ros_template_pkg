// ************************************
// Copyrights by Jin Fagang
// 6/25/19-25-18
// wavehands_stop_node
// jinfagang19@gmail.com
// CTI Robotics
// ************************************


//
// Created by jintain on 6/25/19.
//

#include "ros/ros.h"
#include "wavehands_stop.h"

using namespace perception;


int main(int argc, char **argv) {

  ros::init(argc, argv, "wavehands_stop");
  WaveHandsStop app;
  app.Run();
  return 0;
}