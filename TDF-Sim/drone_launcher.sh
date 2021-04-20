!#/bin/bash

DRONE_SWARM_MEMBERS=$1
INITIAL_HEIGHT=4
MAV_NAME="hummingbird"

if [ -z $DRONE_SWARM_MEMBERS ] # Check if DRONE_SWARM_MEMBERS is NULL
  then
  	#Argument 1 empty
    	echo "-Setting Swarm Members = 1"
    	DRONE_SWARM_MEMBERS=1
  else
    	echo "-Setting DroneSwarm Members = $1"
fi

gnome-terminal  \
--tab --title "Spawn_mav $DRONE_SWARM_MEMBERS" --command "bash -c \"
roslaunch rotors_gazebo spawn_mav_tdf.launch --wait \
    namespace:=$MAV_NAME$DRONE_SWARM_MEMBERS \
    mav_name:=$MAV_NAME \
    x:=$DRONE_SWARM_MEMBERS \
    z:=$INITIAL_HEIGHT \
    log_file:=$MAV_NAME$DRONE_SWARM_MEMBERS;
exec bash\""  &

NUMID_DRONE=11$DRONE_SWARM_MEMBERS
DRONE_SWARM_ID=$DRONE_SWARM_MEMBERS
MAV_NAME=hummingbird
export AEROSTACK_PROJECT=${AEROSTACK_STACK}/../TDF-SARUS/TDF-Sim

#---------------------------------------------------------------------------------------------
# INTERNAL PROCESSES
#---------------------------------------------------------------------------------------------
gnome-terminal  \
`#---------------------------------------------------------------------------------------------` \
`# Basic Behaviors                                                                             ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Basic Behaviors" --command "bash -c \"
roslaunch basic_quadrotor_behaviors basic_quadrotor_behaviors.launch --wait \
    namespace:=drone$NUMID_DRONE;
exec bash\"" \
`#---------------------------------------------------------------------------------------------` \
`# Quadrotor Motion With PID Control                                                           ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Quadrotor Motion With PID Control" --command "bash -c \"
roslaunch quadrotor_motion_with_pid_control quadrotor_motion_with_pid_control.launch --wait \
    namespace:=drone$NUMID_DRONE \
    robot_config_path:=${AEROSTACK_PROJECT}/configs/drone$NUMID_DRONE;
exec bash\""  \
`#---------------------------------------------------------------------------------------------` \
`# Gazebo Interface                                                                            ` \
`#---------------------------------------------------------------------------------------------` \
  --tab --title "Gazebo Interface" --command "bash -c \"
roslaunch gazebo_interface gazebo_interface.launch --wait \
    robot_namespace:=drone$NUMID_DRONE \
    drone_id:=$DRONE_SWARM_ID \
    mav_name:=$MAV_NAME;
exec bash\""  \
`#---------------------------------------------------------------------------------------------` \
`# Gazebo motor speed controller                                                               ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Motor speed controller"  --command "bash -c \"
roslaunch motor_speed_controller motor_speed_controller.launch --wait \
  namespace:=drone$NUMID_DRONE \
  mav_name:=$MAV_NAME;
exec bash\"" \
`#---------------------------------------------------------------------------------------------` \
`# Gazebo Filter Frame Detector                                                                ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Gazebo Filter Frame Detector"  --command "bash -c \"
roslaunch filter_frames filter_frames.launch --wait \
  namespace:=drone$NUMID_DRONE;
exec bash\"" &

sleep 10
rosservice call /drone$NUMID_DRONE/basic_quadrotor_behaviors/behavior_self_localize_with_ground_truth/activate_behavior "timeout: 10000"
rosservice call /drone$NUMID_DRONE/quadrotor_motion_with_pid_control/behavior_quadrotor_pid_motion_control/activate_behavior "timeout: 10000"
rosservice call /drone$NUMID_DRONE/quadrotor_motion_with_pid_control/behavior_quadrotor_pid_thrust_control/activate_behavior "timeout: 10000"
rosservice call /drone$NUMID_DRONE/path_tracker_process/start
#---------------------------------------------------------------------------------------------
# SHELL INTERFACE
#---------------------------------------------------------------------------------------------
gnome-terminal  \
`#---------------------------------------------------------------------------------------------` \
`# alphanumeric_viewer                                                                         ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "alphanumeric_viewer"  --command "bash -c \"
roslaunch alphanumeric_viewer alphanumeric_viewer.launch --wait \
    drone_id_namespace:=drone$NUMID_DRONE;
exec bash\""  &
gnome-terminal  \
`#---------------------------------------------------------------------------------------------` \
`# keyboard_teleoperation_with_pid_control                                                     ` \
`#---------------------------------------------------------------------------------------------` \
--title "keyboard_teleoperation_with_pid_control"  --command "bash -c \"
roslaunch keyboard_teleoperation_with_pid_control keyboard_teleoperation_with_pid_control.launch --wait \
  drone_id_namespace:=drone$NUMID_DRONE;
exec bash\""  
