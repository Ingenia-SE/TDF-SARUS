<img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/logo-color.png?raw=true" alt="TDF-Logo" width="210">

#  SARUS Project

This GitHub repository is home to SARUS, a project in progress by The Drone Face, a INGENIA Systems Engineering (ISE) team.
The aim of the project is to develop a complex system of coordinated drones that will perform Search and Rescue tasks in the mountains. It shall support rescue teams in order to save as much time as possible, thus, as many lives as possible.
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
- Visualizing drones' cameras.

<details>
  <summary><b>Images 🖼️</b></summary>
  
  <b>User interface:</b> featuring all the displays, buttons and controls of the swarm. The map shows the drawn polygon (search area) and the defined path for each drone.
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/ui1.jpeg?raw=true" alt="user_interface" width="500">
  <br>
  <b>User interface integration with the simulation world.</b> The mission logs every detection and the drone position.
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/ui2.jpeg?raw=true" alt="user_interface_and_gazebo" width="500">
  <br>
  <b>User interface integration with the simulation world.</b> The interface can display what the drone is seeing and detecting.
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/ui3.jpeg?raw=true" alt="user_interface_and_gazebo_cameras" width="500">
  <br>

</details>
<br>

### Mission Planner
Integrated into the User Interface, given a polygon and swarm size, it will sort the drones into different areas.

<h4 align="center">They will be flying through an optimal path.</h4>


### Computer Vision
Our drones are equipped with two cameras: RGB and thermal. Consequently, they get two different perceptions of the environment.

The RGB camera is used to run the tiny-YOLOv2 neural network, in order to search for people in the environment. We’ve trained the NN to maximize the effectivity of person detection with our custom dataset. The NN can detect people and different animals such as cows, deers and wolves.

The thermal camera allows the user a quickly check of the detections made by the NN.

Both images are sent to the user interface when a person is detected.

<details>
  <summary><b>Images 🖼️</b></summary>
  
  <b>RGB camera</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Vision/img/rgb-person.jpg?raw=true" alt="tdf_vision_rgb" width="300">
  <br>
  <b>Thermal camera</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Vision/img/thermal-person.jpg?raw=true" alt="tdf_vision_thermal" width="300">
  <br>
  <b>YOLO detection</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Vision/img/yolo-person.png?raw=true" alt="tdf_vision_yolo" width="300">
  <br>
  <b>Received on the interface</b>
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/TDF-Vision/img/vision-interface.jpeg?raw=true" alt="tdf_vision_interface" width="500">

  </details>
  <br>


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
  
## Installation

<b>Requirements:</b> Ubuntu 18.04 & ROS Melodic.

First of all, make sure you have got installed [Aerostack 4.0](https://github.com/cvar-upm/aerostack/wiki/Install-from-source-code) from the source code. In case you don't have it installed, press the link and install accordingly.

#### Clone the repository and access the folder
Go to the Aerostack workspace created on the installation, and clone this repository.

```
cd $AEROSTACK_WORKSPACE/src
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
chmod +x TDF-MissionPlanning/install_dependencies.sh
TDF-MissionPlanning/install_dependencies.sh
sudo apt install ros-melodic-mapviz -y
sudo apt install ros-melodic-mapviz-plugins -y
sudo apt install ros-melodic-tile-map -y
```

Install the modified drone URDF model:

```
cp $AEROSTACK_WORKSPACE/src/TDF-SARUS/TDF-Sim/urdf/hummingbird_tdf.xacro $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_description/urdf/
mv -nv $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav.launch $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/spawn_mav_bak.launch
cp $AEROSTACK_WORKSPACE/src/TDF-SARUS/TDF-Sim/urdf/spawn_mav_tdf.launch $AEROSTACK_WORKSPACE/src/aerostack_stack/stack/simulation/quadrotor_gazebo_simulator/rotors_simulator/rotors_gazebo/launch/
```

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
~/workspace/ros/aerostack_catkin_ws/src/TDF-SARUS/TDF-C2
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
~/workspace/ros/aerostack_catkin_ws/src/TDF-SARUS/TDF-Sim
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
7. In a couple seconds, the calculated mission plan will be displayed on the map, with different colours representing different drone paths, and the drones will proceed to execute the mission. Once it is done, the drones will stay on the last waypoint, and await further instructions (you could create a new search area/polygon, and send it, and they will execute it as before)

To terminate the entire system, you can use the script located on the TDF-Sim folder called stop.sh, like so:

```
./stop.sh
```

This will kill all the running ROS processes. To close all the extra unused terminal windows, run:

```
killall bash
```

### Using CUDA for computer vision

If you've got an NVIDIA Graphics Card in your computer, you may be interested in running the YOLO with your GPU instead of with your CPU, as the execution times will be substancially lower. In case your GPU is not NVIDIA, you'll have to use your CPU then.

This guide is for Ubuntu 18.04 and the installed version of CUDA will be 10.2.

- Check your GPU compatibility. [Click here](https://en.wikipedia.org/wiki/CUDA#GPUs_supported) and find your GPU in the list. Check if your GPU's compute capability is between 3.0 and 7.5. If so, go to the next step.
If your compute capability is not between this range, this guide won't be useful for you.
- Remove any leftout of NVIDIA in your storage.

  ```
  sudo rm /etc/apt/sources.list.d/cuda*
  sudo apt remove --autoremove nvidia-cuda-toolkit
  sudo apt remove --autoremove nvidia-*
  ```

- Add the CUDA PPA repository.

  ```
  sudo apt update
  sudo add-apt-repository ppa:graphics-driverssudo apt-key adv --fetch-keys  http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/7fa2af80.pub
  sudo bash -c 'echo "deb http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64 /" > /etc/apt/sources.list.d/cuda.list'
  sudo bash -c 'echo "deb http://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1804/x86_64 /" > /etc/apt/sources.list.d/cuda_learn.list'
  ```

- Install the CUDA and CUDNN packages.

  ```
  sudo apt update
  sudo apt install cuda-10-2
  sudo apt install libcudnn7
  ```

- Specify the CUDA PATH in the following files.

  ```
  sudo nano ~/.profile
  ```

  And add to the end of the file the following lines:

  ```
  # set PATH for cuda 10.2 installation
  if [ -d "/usr/local/cuda-10.2/bin/" ]; then
  export PATH=/usr/local/cuda-10.2/bin${PATH:+:${PATH}}
  export LD_LIBRARY_PATH=/usr/local/cuda-10.2/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
  fi
  ```

  As well, add these lines to the end of the following file:

  ```
  sudo nano ~/.bashrc
  ```

  ```
  export PATH=/usr/local/cuda-10.2/bin${PATH:+:${PATH}}
  export LD_LIBRARY_PATH=/usr/local/cuda-10.2/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
  ```

- Reboot the computer.
- Verify they're correctly installed and referred in the PATH.

  Check the CUDA compilation tools version by doing:
  ```
  nvcc --version
  ```

  Verify that the NVIDIA drivers are installed:
  ```
  nvidia-smi
  ```

  Verify that the CUDNN library is correctly installed:
  ```
  /sbin/ldconfig -N -v $(sed ‘s/:/ /’ <<< $LD_LIBRARY_PATH) 2>/dev/null | grep libcudnn
  ```
  
  If you get an error by executing the last line, replace the " by '.

  Check that the PATHs are correctly stablished by executing the commands in the following picture and see that the CUDA PATH appear there.
  <br>
  <img src="https://github.com/Ingenia-SE/TDF-SARUS/blob/main/img/cudapath.jpg?raw=true" alt="cudapath" width="500">

- You're done installing it!
