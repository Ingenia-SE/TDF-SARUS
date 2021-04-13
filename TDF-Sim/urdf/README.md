# import_urdf.sh

### What does it do?
It copies the ```hummingbird_tdf.xacro``` and ```spawn_mav_tdf.launch``` to the folders they should be placed.
The ```spawn_mav.launch``` is a temporary solution until a proper TDF Aerostack project is created. It just forces the custom drone to be spawned.

### What do you have to do?
Place all the files in this folder (excepting this README.md) into your ```aerostack_catkin_ws/``` folder, which is normally located at:
```
cd ~/workspace/ros/aerostack_catkin_ws/
```

Then, you just need to run the shell script by typing:
```
./import_urdf.sh
```

If you want to remove urdf files from aerostack, run the following shell script:
```
./remove_urdf.sh
```
