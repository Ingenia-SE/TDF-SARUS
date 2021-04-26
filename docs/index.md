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

First of all, make sure you have got installed [Aerostack 4.0](https://github.com/cvar-upm/aerostack/wiki/Install-from-source-code) from the source code. In case you don't have it installed, press the link.

#### Clone the repository and access the folder

```
git clone https://github.com/Ingenia-SE/TDF-SARUS.git
cd TDF-SARUS
```

#### Importing all the packages into the Aerostack catkin_ws

```
cp -r TDF-Vision/src/ $AEROSTACK_WORKSPACE/src/
cp -r TDF-Sim/tdf_gazebo/ $AEROSTACK_WORKSPACE/src/
cp -r TDF-C2/ $AEROSTACK_WORKSPACE/src/
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

<details>
  <summary><b>Using CUDA for computer vision</b></summary>
  
  </details>
  <br>
