#!/bin/bash

gnome-terminal  \
   	--tab --title "Env_mav" --command "bash -c \"
roslaunch $AEROSTACK_STACK/../TDF-Sim/tdf_gazebo/launch/tdf_gazebo.launch;
						exec bash\""  &

. ${AEROSTACK_STACK}/config/mission/setup.sh