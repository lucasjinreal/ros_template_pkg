/**
 *
 *
 * Publish global 3d map
 * so that we can get octomap
 * */

#include "include/wavehands_stop.h"


using namespace perception;


int main(int argc, char **argv) {

  ros::init(argc, argv, "wavehands_stop");
  WaveHandsStop app;
  app.Run();
  return 0;
}