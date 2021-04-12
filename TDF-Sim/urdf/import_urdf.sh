#!/bin/bash

mv -fv  hummingbird_tdf.xacro src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_description/urdf/
mv -nv src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav.launch src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav_bak.launch
mv -fv spawn_mav.launch src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/
echo Done
