#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <vector>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/BatteryState.h"
#include "aerostack_msgs/ActivateBehavior.h"
#include "aerostack_msgs/DeactivateBehavior.h"
#include <thread>

namespace Ui {
class TestPluginWidget;
}

class TestPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestPluginWidget(QWidget *parent = nullptr);
    ~TestPluginWidget();

    void init_ROS_Node();

private slots:

    void Update_Display();
    void Update_Time();

    void on_addDrone_clicked();

    void on_removeDrone_clicked();

    void on_drone_ID_activated(int index);

    void on_batteryLevelChanged(int nValue);

    void on_land_clicked();

    void on_button_takeoff_clicked();

    void on_launch_simulation_clicked();

    void on_mission_abort_clicked();

    void on_emergency_stop_clicked();

private:
    Ui::TestPluginWidget *ui;

    // Node Handle
    ros::NodeHandle ros_node_handle;

    //Publishers
    ros::Publisher buttonPublisher;
    ros::Publisher landPublisher;
    ros::Publisher emergencyPublisher;
    ros::Publisher n_drones;

    //Subscribers
    ros::Subscriber speedx;
    ros::Subscriber speedy;
    ros::Subscriber speedz;

    ros::Subscriber posex;
    ros::Subscriber posey;
    ros::Subscriber posez;

    ros::Subscriber initial;

    ros::Subscriber pos_z;
    ros::Subscriber battery_level;

    ros::Subscriber drone_detection;
    std::vector<ros::Subscriber> led_detection;

    ros::Subscriber drone_detection_pose;
    std::vector<ros::Subscriber> pose_detection;

    // Clients
    ros::ServiceClient take_off_client;
    ros::ServiceClient land_client;
    ros::ServiceClient mission_stop_client;
    ros::ServiceClient mission_send_client;
    std::vector<ros::ServiceClient> take_off_all;
    std::vector<ros::ServiceClient> land_all;
    std::vector<ros::ServiceClient> mission_stop_all;
    std::vector<ros::ServiceClient> mission_send_all;

    // Subscribers callbacks
    void ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx);
    void ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy);
    void ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz);
    void ros_posex_callback(const geometry_msgs::PoseStamped::ConstPtr &x);
    void ros_posey_callback(const geometry_msgs::PoseStamped::ConstPtr &y);
    void ros_posez_callback(const geometry_msgs::PointStamped::ConstPtr &z);
    void ros_initial_poses_callback(const geometry_msgs::PoseStamped::ConstPtr &pz);
    void ros_batlevel_callback(const sensor_msgs::BatteryState::ConstPtr &percentage);
    void ros_leddetection_callback(const sensor_msgs::ImageConstPtr& frame_detect, int drone_ID);
    void ros_posedetection_callback(const geometry_msgs::PoseStamped::ConstPtr &pose_detected, int drone_ID);
    
    // Variables
    QString droneSpeed_x;
    QString droneSpeed_y;
    QString droneSpeed_z;
    QString dronePos_x;
    QString dronePos_y;
    QString dronePos_z;
    std::vector<int> initial_poses_x;
    std::vector<int> initial_poses_y;
    std::vector<int> initial_poses_z;
    float droneAltitude;
    int droneBat_level;
    int num_Drones = 0;
    std_msgs::String total_drones;
    int led_timer = 0;
    std::vector<int> current_detec;
    
    QTimer *timer_1;
    QTimer *timer_1s;

    QString terminal_msg;
    QString terminal_time;

    QString terminal_msg2;
    QString terminal_time2;

    QString dronePose_x;
    QString dronePose_y;
    QString dronePose_z;
    

    // Simulation thread
    std::thread thread_simulation;
    void launch_simulation();
    bool sim_active = false, sim_running = false, sim_stop = false;
};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
