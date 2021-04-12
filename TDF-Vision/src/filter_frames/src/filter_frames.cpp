
#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include <iostream>
#include <vector>
#include <string>
#include <image_transport/image_transport.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/ObjectCount.h>

// Defines macros of yolo ids
#define ID_victim 99
#define ID_cow 100
#define ID_dog 101

class filter
{

public:

  filter() : img_(nodeHandler){
    
    nodeHandler.param("use_sim_time", use_sim_time, false); // if using simulation time put it as true
    
    // subs
    YOLO_Subscriber_ = img_.subscribe("darknet_ros/detection_image", 1, &filter::callbackYOLO_image, this);
    Objects_Subscriber_ = nodeHandler.subscribe("darknet_ros/found_object", 5, &filter::callbackYOLO_object, this);
    
    // Uncomment if prefer to only publish if ID_detections are provided
    //BB_Subscriber_ = nodeHandler.subscribe("darknet_ros/bounding_boxes", 5, &filter::callbackYOLO_detections, this);
    
    // pubs
    Publisher_ = img_.advertise("sarus_c2/filtered_frames", 5);


  }

  ~filter()
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
      Publisher_.publish(last_image_yolo);

    }


  }
  void 
  callbackYOLO_object(const darknet_ros_msgs::ObjectCountConstPtr& msg)
  {

    // Receive new object message from the yolo

    if(msg->count > 0) // if there are objects detected
    {

      yolo_detection = true;

    }else
    {

      yolo_detection = false;

    }

  }

  void 
  callbackYOLO_detections(const darknet_ros_msgs::BoundingBoxesConstPtr& msg)
  {

    // Receive new object message from the yolo

    for (unsigned i = 0; i < msg->bounding_boxes.size(); i ++)
    {

      // include here the MACROS id of the desired detections to notify the system
      if(msg->bounding_boxes[i].id == ID_victim ||
         msg->bounding_boxes[i].id == ID_cow ||
         msg->bounding_boxes[i].id == ID_dog)  // if there are objects detected
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

private:

  ros::NodeHandle nodeHandler;

  image_transport::ImageTransport img_;

  image_transport::Subscriber YOLO_Subscriber_;
  ros::Subscriber Objects_Subscriber_;
  //ros::Subscriber BB_Subscriber_;

  image_transport::Publisher Publisher_;

  sensor_msgs::Image last_image_yolo;
  bool yolo_detection = false;

  std_msgs::Header prev;
  std_msgs::Header current;

  bool use_sim_time;

};



int main(int argc, char **argv)
{

  ros::init(argc, argv, "filter_frames_node");

  filter filter_node;

  ros::spin();

  return 0;
}

