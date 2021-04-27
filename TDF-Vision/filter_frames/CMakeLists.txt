cmake_minimum_required(VERSION 2.8.3)
project(filter_frames)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
			roscpp 
			roslaunch
			sensor_msgs 
			image_transport
			darknet_ros_msgs
			)


## Declare a catkin package
catkin_package()


roslaunch_add_file_check(launch)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(filter_frames_node src/filter_frames.cpp)
target_link_libraries(filter_frames_node ${catkin_LIBRARIES})
add_dependencies(filter_frames_node sensor_msgs image_transport darknet_ros_msgs)


