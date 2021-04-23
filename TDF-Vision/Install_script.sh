mkdir ~/darknet_ws ####!!!!CAMBIAR POR EL WORKSPACE
mkdir ~/darknet_ws/src

cd ~/darknet_ws/src
git clone --recursive git@github.com:leggedrobotics/darknet_ros.git
cd ..
catkin_make darknet_ros -DCMAKE_BUILD_TYPE=Release
source devel/setup.bash
