# YOLO filter frames
Filter yolo output and publish it when both detections or particular detections are provided. The ROS node is implemented in C++. 

## Previous requisites
You must have built darknet_ros_msgs because are the output of the [YOLO NET](https://github.com/leggedrobotics/darknet_ros).

## Build the package

```
source /opt/ros/melodic/setup.bash
cd catkin_ws/
source devel/setup.bash
cd src/
git clone https://github.com/rsanchezm98/filter_frames.git
cd ..
catkin_make
```
## Run the node
You can run an individual node via rosrun:
```
rosrun filter_frames filter_frames_node
```
Or one or more via roslaunch:
```
roslaunch filter_frames filter_frames.launch
```
