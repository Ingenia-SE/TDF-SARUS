#!/bin/bash

gnome-terminal  \
   	--tab --title "Env_mav" --command "bash -c \"
roslaunch tdf_gazebo sarus_simulation_gazebo.launch;
						exec bash\""  &

. ${AEROSTACK_STACK}/config/mission/setup.sh