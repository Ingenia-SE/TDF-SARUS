#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <vector>
#include <QTimer>
#include <QTime>
#include <QString>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "sensor_msgs/BatteryState.h"
#include "aerostack_msgs/ActivateBehavior.h"


#define FIRST_ID 111

// Leds style
QString LedOff("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgb(46, 52, 54), stop:1 rgb(0, 0, 0));");
QString LedOn_green("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");
QString LedOn_red("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");
QString LedOn_orange("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.232, y1:0.272, x2:0.98, y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
QString LedOn_blue("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.04, y1:0.0565909, x2:0.799, y2:0.795, stop:0 rgba(203, 220, 255, 255), stop:0.41206 rgba(0, 115, 255, 255), stop:1 rgba(0, 49, 109, 255));");

TestPluginWidget::TestPluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPluginWidget)
{
    ui->setupUi(this);

    timer_1 = new QTimer(this);
    QObject::connect(timer_1, SIGNAL(timeout()), this, SLOT(Update_Display()));
    timer_1->start(500);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(Update_Time()));
    timer_1s->start(1000);

    terminal_time = QString("<span style=\" color:red;\">%1</span>").arg(QTime::currentTime().toString("hh:mm:ss"));
    terminal_msg = QString("<span style=\" color:black;\">%1</span>").arg(" MISSION START\n");
    ui->terminal->setText(terminal_time+terminal_msg);

}

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here

    delete ui;
}


void TestPluginWidget::Update_Display() {

    std::string speed;

    int currentDron;
    currentDron = ui->drone_ID->currentIndex();

    ui->speedX->setText(droneSpeed_x);
    ui->speedY->setText(droneSpeed_y);
    ui->speedZ->setText(droneSpeed_z);
    ui->altitude->setText(dronePos_z);
    if(2 > droneAltitude)
    {
        ui->led_Altitude->setStyleSheet(LedOn_green);
    } else {
        ui->led_Altitude->setStyleSheet(LedOff);
    }
    if(20 > droneBat_level)
    {
        ui->led_Battery->setStyleSheet(LedOn_green);
    } else {
        ui->led_Battery->setStyleSheet(LedOff);
    }
    on_batteryLevelChanged(droneBat_level);

}

void TestPluginWidget::Update_Time() {
    ui->current_time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void TestPluginWidget::ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx){
    this->droneSpeed_x = QString::number(vx->twist.linear.x);
}

void TestPluginWidget::ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy){
    this->droneSpeed_y = QString::number(vy->twist.linear.y);
}

void TestPluginWidget::ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz){
    this->droneSpeed_z = QString::number(vz->twist.linear.z);
}

void TestPluginWidget::ros_posz_callback(const geometry_msgs::PointStamped::ConstPtr &pz){
    this->dronePos_z = QString::number((pz->point.z)*(-1));
    this->droneAltitude = (pz->point.z)*(-1);
}

void TestPluginWidget::ros_batlevel_callback(const sensor_msgs::BatteryState::ConstPtr &msg){
    this->droneBat_level = (int)(msg->percentage)*100;
}

void TestPluginWidget::init_ROS_Node()
{
    // Write initialization code here

    // PUBLISHERS
     buttonPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);
     landPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);
     emergencyPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);

    // CLIENTS
    //take_off_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>("/drone111/basic_quadrotor_behaviors/behavior_take_off/activate_behavior");
    land_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>("/drone111/basic_quadrotor_behaviors/behavior_land/activate_behavior");

}




void TestPluginWidget::on_addDrone_clicked()
{
    std::string take_off("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/basic_quadrotor_behaviors/behavior_take_off/activate_behavior"));
    take_off_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>(take_off);
    take_off_all.push_back(take_off_client);

    num_Drones++;
    ui->drone_ID->addItem(QString::number(num_Drones));
    ui->n_drones->setText(QString::number(num_Drones));

}

void TestPluginWidget::on_removeDrone_clicked()
{
    if (num_Drones > 0){
        num_Drones--;
        ui->drone_ID->removeItem(num_Drones);
        take_off_all.pop_back();
    }
    ui->n_drones->setText(QString::number(num_Drones));
}




void TestPluginWidget::on_drone_ID_activated(int index)
{
    std::string speed("/drone" + (std::to_string(FIRST_ID+index) + "/motion_reference/speed"));
    std::string altitude("/drone" + (std::to_string(FIRST_ID+index) + "/sensor_measurement/altitude"));
    std::string battery("/drone" + (std::to_string(FIRST_ID+index) + "/sensor_measurement/battery_state"));

    speedx = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedx_callback, this);
    speedy = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedy_callback, this);
    speedz = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedz_callback, this);
    pos_z = ros_node_handle.subscribe(altitude, 1, &TestPluginWidget::ros_posz_callback, this);
    battery_level = ros_node_handle.subscribe(battery, 1, &TestPluginWidget::ros_batlevel_callback, this);
}

void TestPluginWidget::on_batteryLevelChanged(int nValue)
{
    ui->BatteryProgressBar->setValue(nValue);
    ui->BatteryProgressBar->setAlignment(Qt::AlignCenter);
    QString myStyleSheet = " QProgressBar::chunk {"
    " background-color: ";

    if(20 > nValue)
    {
        myStyleSheet.append("red;");
    }
    else if(60 > nValue && 20 <= nValue)
    {
        myStyleSheet.append("yellow;");
    }
    else
    {
        myStyleSheet.append("green;");
    }
    myStyleSheet.append("     width: 10px;"\
                    "     margin: 0px;"\
                    " }");
    ui->BatteryProgressBar->setStyleSheet(myStyleSheet);

}

void TestPluginWidget::on_land_clicked()
{
    // Button clicked callback
        std_msgs::String message;
        message.data = "Land clicked!";
        landPublisher.publish(message);

        aerostack_msgs::ActivateBehavior srv;
        srv.request.arguments = "";
        srv.request.timeout = 1000;
        if(land_client.call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack) ROS_INFO("Acknowledged!");
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
}

void TestPluginWidget::on_button_takeoff_clicked()
{
    // Button clicked callback
    std_msgs::String message;
    message.data = "Button clicked!";
    buttonPublisher.publish(message);

    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::ActivateBehavior srv;
        srv.request.arguments = "";
        srv.request.timeout = 1000;
        if(take_off_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack) ROS_INFO("Acknowledged!");
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
    }

}
