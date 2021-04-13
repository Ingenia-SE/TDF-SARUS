#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <vector>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "sensor_msgs/BatteryState.h"
#include "aerostack_msgs/ActivateBehavior.h"
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

private:
    Ui::TestPluginWidget *ui;

    // Node Handle
    ros::NodeHandle ros_node_handle;

    //Publishers
    ros::Publisher buttonPublisher;
    ros::Publisher landPublisher;
    ros::Publisher emergencyPublisher;

    //Subscribers
    ros::Subscriber speedx;
    ros::Subscriber speedy;
    ros::Subscriber speedz;
    ros::Subscriber pos_z;
    ros::Subscriber battery_level;

    // Clients
    ros::ServiceClient land_client;
    ros::ServiceClient emergency_stop_client;
    ros::ServiceClient take_off_client;
    std::vector<ros::ServiceClient> take_off_all;

    // Subscribers callbacks
    void ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx);
    void ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy);
    void ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz);
    void ros_posz_callback(const geometry_msgs::PointStamped::ConstPtr &z);
    void ros_batlevel_callback(const sensor_msgs::BatteryState::ConstPtr &percentage);

    // Variables
    QString droneSpeed_x;
    QString droneSpeed_y;
    QString droneSpeed_z;
    QString dronePos_z;
    float droneAltitude;
    int droneBat_level;
    int num_Drones = 0;

    QTimer *timer_1;
    QTimer *timer_1s;

    QString terminal_msg;
    QString terminal_time;

    // Simulation thread
    std::thread thread_simulation;
    void launch_simulation();
    bool sim_active = false, sim_running = false, sim_stop = false;
};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
