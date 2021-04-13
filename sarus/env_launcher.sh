#!/bin/bash

gnome-terminal  \
   	--tab --title "Env_mav" --command "bash -c \"
roslaunch rotors_gazebo env_mav.launch;
						exec bash\""  &

. ${AEROSTACK_STACK}/config/mission/setup.sh