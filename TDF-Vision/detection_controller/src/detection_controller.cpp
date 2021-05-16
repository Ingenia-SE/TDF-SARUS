#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include <iostream>
#include <vector>
#include <string>
#include <image_transport/image_transport.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/ObjectCount.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>

// Defines macros of yolo ids
#define ID_victim 0


class detector
{

public:

  detector() : img_(nodeHandler){
    
    nodeHandler.param("use_sim_time", use_sim_time, true); // if using simulation time put it as true
    
    // subcription to the detection image provided by the yolo node
    m_YoloSubscriber = img_.subscribe("darknet_ros/darknet_ros/detection_image", 1, &detector::callbackYOLO_image, this);
    
    // subscription to yolo detected bounding boxes
    m_BbSubscriber = nodeHandler.subscribe("darknet_ros/darknet_ros/bounding_boxes", 5, &detector::callbackYOLO_detections, this);

    // subscription to drone pose
    m_PoseSubscriber = nodeHandler.subscribe("ground_truth/pose", 5, &detector::dronePoseCallback, this);
    
    // image publisher
    m_ImagePublisher = img_.advertise("sarus_c2/filtered_frames", 5);

    // pose publisher
    m_PosePublisher = nodeHandler.advertise<geometry_msgs::PoseStamped>("sarus_c2/detection_pose", 5);

  }

  ~detector()
  {

  }


  void 
  callbackYOLO_image(const sensor_msgs::ImageConstPtr& msg)
  {

    // Latency computation to debug fps of the image that is received
    current.stamp = ros::Time::now();
    double difference = freq_(current, prev);
    std::cout << "[YOLO_image]: Current Avg Sub Rate: " << difference << "Hz" << std::endl;
    prev = current;
    
    // keep the image
    last_image_yolo = *msg;

    if (yolo_detection) // if the image has objects
    {
      yolo_detection = false;
      std::cout << "[YOLO_image]: Publishing image with detections" << std::endl;
      m_ImagePublisher.publish(last_image_yolo);

      // we also publish the pose coordinates of the drone
      m_PosePublisher.publish(m_LastPose);

    }

  }


  void 
  callbackYOLO_detections(const darknet_ros_msgs::BoundingBoxesConstPtr& msg)
  {

    // Receive new object message from the yolo

    for (unsigned i = 0; i < msg->bounding_boxes.size(); i ++)
    {
     
      // include here the MACROS id of the desired detections to notify the system
      if(msg->bounding_boxes[i].id == ID_victim)  // if there are objects detected
      {

        yolo_detection = true;

      }else
      {

        yolo_detection = false;  

      }
      
    }
    
  }

  double 
  freq_(std_msgs::Header current, std_msgs::Header prev)
  {

    long secs = ((long) current.stamp.sec - (long) prev.stamp.sec);
    long nsecs = ((long) current.stamp.nsec - (long) prev.stamp.nsec);

    double latency = (double) secs*1000 + (double) nsecs/1000000;

    double freq = 1000/latency;

    return freq;

  }

  void
  dronePoseCallback(const geometry_msgs::PoseStamped::ConstPtr &pose)
  {
    // we publish a pose msg
    m_LastPose.header = pose->header;
    m_LastPose.pose = pose->pose;
  }

private:

  ros::NodeHandle nodeHandler;

  image_transport::ImageTransport img_;

  image_transport::Subscriber m_YoloSubscriber;
  ros::Subscriber m_BbSubscriber;
  ros::Subscriber m_PoseSubscriber;

  image_transport::Publisher m_ImagePublisher;
  ros::Publisher m_PosePublisher;

  sensor_msgs::Image last_image_yolo;
  bool yolo_detection = false;

  std_msgs::Header prev;
  std_msgs::Header current;

  geometry_msgs::PoseStamped m_LastPose;

  bool use_sim_time;

};



int main(int argc, char **argv)
{

  ros::init(argc, argv, "detection_controller_node");

  detector detector_node;

  ros::spin();

  return 0;
}

