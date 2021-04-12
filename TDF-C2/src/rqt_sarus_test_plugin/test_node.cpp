#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "marti_nav_msgs/Route.h"
#include "marti_nav_msgs/RoutePoint.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "test_node");
    ros::NodeHandle node;
    long unsigned int id = 0;

    ROS_INFO("Created test node");

    ros::Publisher pub = node.advertise<nav_msgs::Path>("/mapviz/path",1);

    ros::Duration seconds_sleep(1);

    nav_msgs::Path path;

    geometry_msgs::PoseStamped pose;

    while(ros::ok()) {

        // First waypoint
        pose.header.frame_id = "world";
        pose.pose.position.x = 100;
        pose.pose.position.y = 100;
        pose.pose.position.z = 100;

        path.header.frame_id = "world";
        path.poses.push_back(pose);

        // Second waypoint
        pose.header.frame_id = "world";
        pose.pose.position.x = 200;
        pose.pose.position.y = 100;
        pose.pose.position.z = 100;

        path.header.frame_id = "world";
        path.poses.push_back(pose);

        // Third waypoint
        pose.header.frame_id = "world";
        pose.pose.position.x = 200;
        pose.pose.position.y = 200;
        pose.pose.position.z = 100;

        path.header.frame_id = "world";
        path.poses.push_back(pose);    

        // Fourth waypoint
        pose.header.frame_id = "world";
        pose.pose.position.x = 400;
        pose.pose.position.y = 200;
        pose.pose.position.z = 100;

        path.header.frame_id = "world";
        path.poses.push_back(pose); 

        pub.publish(path);
        path.poses.clear();

        ros::spinOnce();

        seconds_sleep.sleep();
    }
}