cmake_minimum_required(VERSION 2.8.3)
project(detection_controller)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
			roscpp 
			roslaunch
			sensor_msgs 
			image_transport
			darknet_ros_msgs
			geometry_msgs
			)


## Declare a catkin package
catkin_package()

roslaunch_add_file_check(launch)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})


