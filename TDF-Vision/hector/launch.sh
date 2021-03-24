#!/bin/bash

gnome-terminal  \
--tab --title "gazebo_world" --command "bash -c \"
source ./devel/setup.bash
roslaunch hector_gazebo_worlds rescue_mission.launch ;
exec bash\"" \
--tab --title "spawn" --command "bash -c \"
sleep 5
source ./devel/setup.bash 
roslaunch hector_quadrotor_gazebo spawn_quadrotor_with_thermal.launch;
exec bash\""

