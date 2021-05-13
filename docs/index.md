<img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/logo-color.png?raw=true" alt="TDF-Logo" width="210">

#  The Drone Face - SARUS Project

## What is SARUS?

SARUS is a project made by The Drone Face. Its aim is to develop a complex system of coordinated drones that will perform Search and Rescue tasks in the mountains. It shall support rescue teams in order to save as much time as possible, thus, as many lives as possible.

## Features

The whole project can be divided into its four main modules which have been developed simultaneously.

### User Interface

- Designed to be user-friendly and flexible.
- Easy to manage the swarm:
  - Adding / Removing deployed drones.
  - Individually selecting and controlling drones.
  - Visualizing system warnings and drones' parameters (battery, position...).
- Hand-drawing the searching areas polygons.
- Powerful routes displaying.
- General system messages log.
- Simulated world displayed.
[comment]:<> ( Visualizing drones' cameras.)

<details>
  <summary><b>Images 🖼️</b></summary>
  Images
</details>
<br>

### Mission Planner
Integrated into the User Interface, given a polygon and swarm size, it will sort the drones into different areas.

<h4 align="center">They will be flying through an optimal path.</h4>


### Computer Vision
We've trained a YOLO neural network to maximize the effectivity of person detection with our custom dataset. The NN can detect people and different animals such as cows, deers and wolves.

### tdf_gazebo map
The Simulation Team at TDF has developed a brand new map for their simulation purposes. It features multiple environments to design and test the S&R tasks.
- Collapsed Buildings
- Forest
- Leafy forest
- Base to deploy S&R drones

As well, it features custom gazebo models for animals and people.

<details>
  <summary><b>Images 🖼️</b></summary>
  
  <b>World overview</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Sim/tdf_gazebo/img/world.png?raw=true" alt="tdf_gazebo" width="500">
  <br>
  <b>Collapsed buildings</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Sim/tdf_gazebo/img/ruins.png?raw=true" alt="tdf_gazebo_ruins" width="500">
  <br>
  <b>Base to deploy search and rescue robots</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Sim/tdf_gazebo/img/base.png?raw=true" alt="tdf_gazebo_base" width="500">
  <br>
  <b>Forest</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Sim/tdf_gazebo/img/forest.png?raw=true" alt="tdf_gazebo_forest" width="500">
  <br>
  <b>Leafy forest</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Sim/tdf_gazebo/img/leafy.png?raw=true" alt="tdf_gazebo_leafy" width="500">

  </details>
  <br>
  
## Installation (WIP)

<b>Requirements:</b> Ubuntu 18.04 & ROS Melodic.

First of all, make sure you have got installed [Aerostack 4.0](https://github.com/cvar-upm/aerostack/wiki/Install-from-source-code) from the source code. In case you don't have it installed, press the link and install accordingly.

#### Clone the repository and access the folder

Go to the Aerostack workspace created on the installation, and clone this repository.

```
cd $AEROSTACK_WORKSPACE
git clone https://github.com/Ingenia-SE/TDF-SARUS.git
cd TDF-SARUS
```

#### Place the darknet_ros package

This is neccesary, otherwise, the project will not compile.

```
mv -r TDF-Vision/darknet_ros/ $AEROSTACK_WORKSPACE/src/
```

#### Install all dependencies

```
chmod +x TDF-MissionPlanning/mission_setup.sh
./mission_setup.sh
sudo apt install ros-melodic-mapviz -y
sudo apt install ros-melodic-mapviz-plugins -y
sudo apt install ros-melodic-tile-map -y
```
[comment]:<> (Don't forget URDF.)

## Setup Guide

Once installed, the catkin workspace must be compiled. To do this, run the following command from the aerostack_catkin_ws directory:

```
catkin_make
```

This will build and link all the source code, including Aerostack and TDF-SARUS modules.
Once it compiles successfully, you can run the system by running:

```
roslaunch rqt_sarus_test_plugin rqt_sarus_gui.launch
```

This will run both the Command and Control GUI, as well as the Mission Planner. If you are running the system for the first time, the rqt interface will pop up without any plugins active yet. SARUS uses two plugins: Test Plugin and Mapviz.

To activate the first one (Test Plugin), click on the Plugins tab, and click on the Test Plugin tab. This will show the different buttons and displays of the system.

To activate the second one (Mapviz), click on the Plugins tab, and go to Visualization>Mapviz. After the Mapviz plugin loads, click on Files>Open Config <u>under the Mapviz plugin</u>, and navigate to:

```
~/workspace/ros/aerostack_catkin_ws/TDF-SARUS/TDF-C2
```

Inside this directory you will find a file named mapviz_config.mvc. Open it, and the mapviz configuration will load (the map will be displayed). 

These configuration steps will only be neccesary the first time you open up the system.

## Simulation Guide

The previous section explains how to get the command and control system up and running. For the complete system to work, drones are needed (either real drones, or simulated ones).

SARUS provides a way to simulate different missions to test the system. First, run the system normally with the command:

```
roslaunch rqt_sarus_test_plugin rqt_sarus_gui.launch
```

Once it is loaded, click on the 'Simulation' button. This will launch the Gazebo simulator with the default world provided by TDF. No drones are added yet, so to do that, open up a terminal in the following directory:

```
~/workspace/ros/aerostack_catkin_ws/TDF-SARUS/TDF-Sim
```

In this directory, there are different helper bash scripts to add drones to the simulation. Two scripts can be used:
- drone_launcher.sh: This script is used for development, it launches a single drone, with all its controllers, but without the detection system. It can be used to test the Mission Planner functionality.
- drone_launcher_darknet.sh: This script launches a single drone, with its detection system, consisting of the Detection Controller and the YOLO neural network architecture for computer vision. It can be used to test the detection functionality of the system.

As an example, to launch and add a drone to the simulation using the drone_launcher.sh script, you only need to run (from the TDF-Sim directory):

```
./drone_launcher.sh 1
```

Make sure to have the adequate execution permissions enabled for this script. This command will launch a drone with the ID number 1. By changing the number that goes after the drone_launcher.sh, and running it again, you can launch more drones with different IDs. Never run the same command twice (collisions will occur), always use different IDs. The system currently supports up to 4 drones, but this is limited by the hardware resources on your machine.

The script will run all the neccesary components for the drone. You should also be able to see it on the Gazebo simulation, and on the map of the C2 user interface.

## User Guide

After all the components are ready, we can begin to use the system to perform a search. Make sure to follow these steps:
1. On the user interface, click on the Add Drone button to add different active drones for the mission (you do not need to use every active drone for the search). 
2. After you have added at least one drone, you can see its telemetry by clicking on the Drone tab, and selecting the appropriate drone ID.
3. Now, after all the drones have been added, you can define the search area of interest simply by clicking on different points of the map, to define a polygon that will be displayed on the user interface. You can drag the points by clicking and dragging, and remove points by right clicking on them.
4. Once you are happy with the search area, click on View on the Mapviz plugin, and make sure that the 'Show Config Panel' option is enabled (though it might already be).
5. Before sending the search area to the Mission Planner, click on the 'Take off' button. This will make all the drones take off, as you can check on the telemetry or the Gazebo simulation.
6. Once it is, go to the Config side of the plugin, and under the draw_polygon (new display) option, click on 'Publish Polygon'. This action will send the polygon you created to the Mission Planner to calculate the mission plan.
7. In a couple seconds, the calculated mission plan will be displayed on the map, with different colours representing different drone paths, and the drones will proceed to execute the mission. Once it is done, the drones will stay on the last waypoint, and await further instructions (you could create a new search area/polygon, and send it, and they will execute it as before).

To terminate the entire system, you can use the script located on the TDF-Sim folder called stop.sh, like so:

```
./stop.sh
```

This will kill all the running ROS processes. To close all the extra unused terminal windows, run:

```
killall bash
```
<details>
  <summary><b>Using CUDA for computer vision</b></summary>
  
  </details>
  <br>
