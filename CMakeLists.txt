cmake_minimum_required(VERSION 2.8.3)
project(wavehands_stop)

# Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED
             COMPONENTS roscpp
                        tf
                        tf_conversions
                        pcl_ros
                        sensor_msgs
                        geometry_msgs
                        pcl_conversions
                        # cti_msgs
             )

catkin_package(INCLUDE_DIRS
               CATKIN_DEPENDS
               roscpp
               tf
               tf_conversions
               pcl_ros
               sensor_msgs
               geometry_msgs
               pcl_conversions
               # cti_msgs
               )

find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
include_directories(include ${catkin_INCLUDE_DIRS})


# !---------------] find libs what wavehands need
set(CMAKE_PREFIX_PATH $ENV{HOME}/libtorch)
find_package(Torch REQUIRED)
include_directories(include/)
if (NOT Torch_FOUND)
    message(FATAL_ERROR "you should change CMAKE_PREFIX_PATH to libtorch dir")
    else()
    message(STATUS "found libtorch at " ${TORCH_LIBRARIES} )
endif()
find_package(OpenCV REQUIRED)
find_library(HUMAN_POSE_ESTIMATION
        NAMES human_pose_estimation
        HINTS ./libs
        PATHS ./libs)


add_executable(wavehands_stop_node src/wavehands_stop_node.cc)
target_link_libraries(wavehands_stop_node ${catkin_LIBRARIES} ${PCL_LIBRARIES} glog)
