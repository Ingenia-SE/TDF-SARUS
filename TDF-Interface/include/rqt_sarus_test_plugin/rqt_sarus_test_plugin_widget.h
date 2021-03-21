#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/TwistStamped.h"


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
    void on_pushButton_clicked();
    void Update_Display();


private:
    Ui::TestPluginWidget *ui;

    // Node Handle
    ros::NodeHandle ros_node_handle;

    // Publishers
    ros::Publisher buttonPublisher;

    // Subscribers
    ros::Subscriber speedx;
    ros::Subscriber speedy;

    // Subscribers callbacks
    void ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx);
    void ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy);

    // Variables
    float dronSpeed_x;
    float dronSpeed_y;
    int num_Drones = 2;

    QTimer *timer_1s;

};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
