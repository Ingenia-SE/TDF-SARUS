#!/bin/bash

cp $AEROSTACK_WORKSPACE/src/TDF-Sim/urdf/hummingbird_tdf.xacro $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_description/urdf/
#mv -nv src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav.launch src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav_bak.launch
cp $AEROSTACK_WORKSPACE/src/TDF-Sim/urdf/spawn_mav_tdf.launch $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/
echo Done
