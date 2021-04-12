# import_urdf.sh

### What does it do?
It moves the ```hummingbird_tdf.xacro``` and ```spawn_mav.launch``` to the folders they should be placed.
The ```spawn_mav.launch``` is a temporary solution until a proper TDF Aerostack project is created. It just forces the custom drone to be spawned.

Thus, a backup file of the original version of ```spawn_mav.launch``` is saved into ```spawn_mav_bak.launch``` in the same folder. In case you were wondering, if ```spawn_mav_bak.launch``` already exists (because you've already run the script before), it will be preserved.

### What do you have to do?
Place all the files in this folder (excepting this README.md) into your ```aerostack_catkin_ws/``` folder, which is normally located at:
```
cd ~/workspace/ros/aerostack_catkin_ws/
```

Then, you just need to run the shell script by typing:
```
./import_urdf.sh
```
