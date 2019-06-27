cmake_minimum_required(VERSION 2.8.3)
project(wavehands_stop)


#add_definitions("-std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1")


find_package(catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        geometry_msgs
        message_filters
        tf_conversions
        tf
        laser_geometry
        cv_bridge
        std_msgs
        cti_msgs
        message_generation)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES semantic_seg
        #  CATKIN_DEPENDS other_catkin_pkg
        #  DEPENDS system_lib
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        #        ${PCL_INCLUDE_DIRS}
)

# !---------------] find libs what wavehands need
set(CMAKE_PREFIX_PATH $ENV{HOME}/libtorch)
find_package(Torch REQUIRED)
include_directories("${TORCH_INCLUDE_DIRS}")

set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1")


if (NOT Torch_FOUND)
    message(FATAL_ERROR "libtorch not found, wavehands_stop will not built.")
else ()
    message(STATUS "++++ found libtorch ")


    find_library(HUMAN_POSE_ESTIMATION
            NAMES human_pose_estimation
            HINTS ./libs
            PATHS ./libs)
    file(GLOB_RECURSE
            SOURCES
            src/*.cc)

    add_executable(wavehands_stop_node ${SOURCES})
    target_link_libraries(
            wavehands_stop_node
            ${catkin_LIBRARIES}
            ${OpenCV_LIBS}
            ${TORCH_LIBRARIES}
            ${HUMAN_POSE_ESTIMATION}
            thor
            glog
    )
    get_target_property(TARGET_LIBRARIES wavehands_stop_node LINK_LIBRARIES)
    message(STATUS "++++ all target libs: " ${TARGET_LIBRARIES})
endif ()








