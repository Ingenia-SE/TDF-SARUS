#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <vector>
#include <QTimer>
#include <QTime>
#include <QString>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/BatteryState.h"
#include "aerostack_msgs/ActivateBehavior.h"
#include "aerostack_msgs/DeactivateBehavior.h"


#define FIRST_ID 111

// Leds style
QString LedOff("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgb(46, 52, 54), stop:1 rgb(0, 0, 0));");
QString LedOn_green("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));");
QString LedOn_red("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));");
QString LedOn_orange("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.232, y1:0.272, x2:0.98, y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255));");
QString LedOn_blue("border: 1px solid grey; border-radius:8px; background-color: qlineargradient(spread:pad, x1:0.04, y1:0.0565909, x2:0.799, y2:0.795, stop:0 rgba(203, 220, 255, 255), stop:0.41206 rgba(0, 115, 255, 255), stop:1 rgba(0, 49, 109, 255));");


/**
 * @brief Test Plugin Constructor
 */

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

    ui->terminal->setWordWrapMode(QTextOption::WordWrap);
    terminal_time = QString("<span style=\" color:red;\">%1</span>").arg(QTime::currentTime().toString("hh:mm:ss"));
    terminal_msg = QString("<span style=\" color:white;\">%1</span>").arg("MISSION START\n");
    ui->terminal->setText(terminal_time + " " + terminal_msg);
}

/**
 * @brief Test Plugin Destructor
 */

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here

    delete ui;
}

/**
 * @brief Update callback for the displays
 */

void TestPluginWidget::Update_Display() {

    std::string speed;

    int currentDron;
    currentDron = ui->drone_ID->currentIndex();

    ui->poseX->setText(dronePos_x);
    ui->poseY->setText(dronePos_y);
    ui->poseZ->setText(dronePos_z);

    ui->speedX->setText(droneSpeed_x);
    ui->speedY->setText(droneSpeed_y);
    ui->speedZ->setText(droneSpeed_z);
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

/**
 * @brief Update callback for the mission time
 */
void TestPluginWidget::Update_Time() {
    ui->current_time->setText(QTime::currentTime().toString("hh:mm:ss"));
    if (led_timer > 2){
        ui->led_Coincidence->setStyleSheet(LedOff);
        led_timer = 0;
        
    }else{
        led_timer++;
    }

    for(int i=0; i< num_Drones; i++){
        if(current_detec[i] > 0){
            if(current_detec[i] > 3)
                current_detec[i] = 0;
            else
                current_detec[i]++;
        }
    }
}

/**
 * @brief ROS topic callbacks
 */

void TestPluginWidget::ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx){
    this->droneSpeed_x = QString::number((int)(vx->twist.linear.x));
}

void TestPluginWidget::ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy){
    this->droneSpeed_y = QString::number((int)(vy->twist.linear.y));
}

void TestPluginWidget::ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz){
    this->droneSpeed_z = QString::number((int)(vz->twist.linear.z));
}

void TestPluginWidget::ros_posex_callback(const geometry_msgs::PoseStamped::ConstPtr &pz){
    this->dronePos_x = QString::number((int)(pz->pose.position.x));
}

void TestPluginWidget::ros_posey_callback(const geometry_msgs::PoseStamped::ConstPtr &pz){
    this->dronePos_y = QString::number((int)(pz->pose.position.y));
}

void TestPluginWidget::ros_posez_callback(const geometry_msgs::PointStamped::ConstPtr &pz){
    this->dronePos_z = QString::number((int)(pz->point.z)*(-1));
    this->droneAltitude = (int)(pz->point.z)*(-1);
}

void TestPluginWidget::ros_batlevel_callback(const sensor_msgs::BatteryState::ConstPtr &msg){
    this->droneBat_level = (int)(msg->percentage)*100;
}

void TestPluginWidget::ros_initial_poses_callback(const geometry_msgs::PoseStamped::ConstPtr &pz){
    this->initial_poses_x.push_back((int)(pz->pose.position.x));
    this->initial_poses_y.push_back((int)(pz->pose.position.y));
    this->initial_poses_z.push_back((int)(pz->pose.position.z));
    ROS_ERROR("Shutdown succeed");
    ROS_ERROR("%s\n",std::to_string(initial_poses_x[0]).data());
    ROS_ERROR("%s\n",std::to_string(initial_poses_y[0]).data());
    ROS_ERROR("%s\n",std::to_string(initial_poses_z[0]).data());
    initial.shutdown();
}

void TestPluginWidget::ros_leddetection_callback(const sensor_msgs::ImageConstPtr& frame_detect, int drone_ID){
    led_timer = 0;
    ui->led_Coincidence->setStyleSheet(LedOn_green);
    
    if(current_detec[drone_ID-1] == 0){
        terminal_time = QString("<span style=\" color:red;\">%1</span>").arg(QTime::currentTime().toString("hh:mm:ss"));
        terminal_msg = QString("<span style=\" color:white;\">%1</span>").arg( "New detection from DRONE " + QString::number(drone_ID) + "\n");
        ui->terminal->append(terminal_time + " " + terminal_msg);
        current_detec[drone_ID-1]++;
    }
}

/**
 * @brief ROS initializer routine: It initializes the node with the subscribed or advertised topics
 */

void TestPluginWidget::init_ROS_Node()
{
    // Write initialization code here

    // PUBLISHERS

     n_drones = ros_node_handle.advertise<std_msgs::String>("n_drones", 1);

    // CLIENTS
}
/**
 * @brief Callback for the add drone button
 */

void TestPluginWidget::on_addDrone_clicked()
{
    // Client for take off functionality
    std::string take_off("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/basic_quadrotor_behaviors/behavior_take_off/activate_behavior"));
    take_off_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>(take_off);
    take_off_all.push_back(take_off_client);

    // Client for landing functionality
    std::string land("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/basic_quadrotor_behaviors/behavior_land/activate_behavior"));
    land_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>(land);
    land_all.push_back(land_client);

    // Client for stop functionality
    std::string stop("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/quadrotor_motion_with_pid_control/behavior_follow_path/deactivate_behavior"));
    mission_stop_client = ros_node_handle.serviceClient<aerostack_msgs::DeactivateBehavior>(stop);
    mission_stop_all.push_back(mission_stop_client);

    // Client for mission sending functionality
    std::string mission("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/quadrotor_motion_with_pid_control/behavior_follow_path/activate_behavior"));
    mission_send_client = ros_node_handle.serviceClient<aerostack_msgs::ActivateBehavior>(mission);
    mission_send_all.push_back(mission_send_client);

    // Subscriber to filter_frames for led detection
    std::string drone_frame("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/sarus_c2/filtered_frames"));
    drone_detection = ros_node_handle.subscribe<sensor_msgs::Image>(drone_frame, 1, boost::bind(&TestPluginWidget::ros_leddetection_callback, this, _1, num_Drones));
    led_detection.push_back(drone_detection);
    current_detec.push_back(0);

    std::string pose("/drone" + (std::to_string(FIRST_ID+num_Drones) + "/ground_truth/pose"));
    initial = ros_node_handle.subscribe<geometry_msgs::PoseStamped>(pose,1,&TestPluginWidget::ros_initial_poses_callback,this);

    num_Drones++;

    ui->drone_ID->addItem(QString::number(num_Drones));
    ui->n_drones->setText(QString::number(num_Drones));
    total_drones.data = std::to_string(num_Drones);
    n_drones.publish(total_drones);
}

/**
 * @brief Callback for the remove drone button
 */
void TestPluginWidget::on_removeDrone_clicked()
{
    if (num_Drones > 0){
        num_Drones--;
        ui->drone_ID->removeItem(num_Drones);
        take_off_all.pop_back();
        land_all.pop_back();
        mission_stop_all.pop_back();
        mission_send_all.pop_back();
        led_detection.pop_back();
        current_detec.pop_back();
    }
    ui->n_drones->setText(QString::number(num_Drones));
    total_drones.data = std::to_string(num_Drones);
    n_drones.publish(total_drones);
}

/**
 * @brief Callback for the drone selection tab
 */

void TestPluginWidget::on_drone_ID_activated(int index)
{
    std::string speed("/drone" + (std::to_string(FIRST_ID+index) + "/motion_reference/speed"));
    std::string altitude("/drone" + (std::to_string(FIRST_ID+index) + "/sensor_measurement/altitude"));
    std::string battery("/drone" + (std::to_string(FIRST_ID+index) + "/sensor_measurement/battery_state"));
    std::string pose("/drone" + (std::to_string(FIRST_ID+index) + "/ground_truth/pose"));
    speedx = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedx_callback, this);
    speedy = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedy_callback, this);
    speedz = ros_node_handle.subscribe(speed, 1, &TestPluginWidget::ros_speedz_callback, this);
    posex = ros_node_handle.subscribe(pose, 1, &TestPluginWidget::ros_posex_callback, this);
    posey = ros_node_handle.subscribe(pose, 1, &TestPluginWidget::ros_posey_callback, this);
    posez = ros_node_handle.subscribe(altitude, 1, &TestPluginWidget::ros_posez_callback, this);
    battery_level = ros_node_handle.subscribe(battery, 1, &TestPluginWidget::ros_batlevel_callback, this);
}

/**
 * @brief Callback for the battery display
 */

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

/**
 * @brief Callback for the take off button
 */

void TestPluginWidget::on_button_takeoff_clicked()
{
    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::ActivateBehavior srv;
        srv.request.arguments = "";
        srv.request.timeout = 1000;
        if(take_off_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack) {
                ROS_INFO("Acknowledged!");
            }
            else {
                ROS_INFO("Not acknowledged");
            } 
        }
        else ROS_ERROR("Service call failed");
    }


}

/**
 * @brief Callback for the land button
 */

void TestPluginWidget::on_land_clicked()
{
    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::ActivateBehavior srv;
        srv.request.arguments = "";
        srv.request.timeout = 1000;
        if(land_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack) ROS_INFO("Acknowledged!");
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
    }
}

/**
 * @brief Callback for the abort button
 */
void TestPluginWidget::on_mission_abort_clicked()
{
    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::DeactivateBehavior srv;
        // srv.request.arguments = "";
        // srv.request.timeout = 1000;
        if(mission_stop_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack){ 
                ROS_INFO("Acknowledged!");
                ros::service::waitForService("/drone" + std::to_string(FIRST_ID+i) + "/quadrotor_motion_with_pid_control/behavior_follow_path/deactivate_behavior",1000);
            }
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
    }
    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::ActivateBehavior srv;
        srv.request.arguments = "path: [ [" + std::to_string(initial_poses_x[i]) + "," + std::to_string(initial_poses_y[i]) + ",15] ]";
        srv.request.timeout = 1000;
        if(mission_send_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack){ 
                ROS_INFO("Acknowledged!");
            }
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
    }
}

/**
 * @brief Callback for the emergency stop button
 */
void TestPluginWidget::on_emergency_stop_clicked()
{
    for(int i=0; i<num_Drones; i++){
        aerostack_msgs::DeactivateBehavior srv;
        //srv.request.arguments = "";
        //srv.request.timeout = 1000;
        if(mission_stop_all[i].call(srv))
        {
            ROS_INFO("Service call succesfull");
            if(srv.response.ack) ROS_INFO("Acknowledged!");
            else ROS_INFO("Not acknowledged");
        }
        else ROS_ERROR("Service call failed");
    }
}

/**
 * @brief Callback for the simulation button
 */

void TestPluginWidget::on_launch_simulation_clicked()
{
    if(!sim_running)
    {
        sim_active = true;
        thread_simulation = std::thread(&TestPluginWidget::launch_simulation, this);
    }
    if(sim_running)
    {
        sim_stop = true;
        std::string kill("gnome-terminal --tab --title 'killer' --command 'killall -9 gzclient gzserver'");
        system(kill.c_str());
        thread_simulation.join();
        sim_running = false;
        sim_stop = false;
    }
}

void TestPluginWidget::launch_simulation()
{
    while(!sim_stop)
    {
        if(sim_active && !sim_running)
        {
            sim_active = false;
            sim_running = true;
            std::cout << "Publishing commands..." << std::endl;
            // change directory
            chdir("/home/workspace/ros/aerostack_catkin_ws/src/TDF-Sim/");
            // publish system command
            std::string myCommand("gnome-terminal --tab --title 'sarus_simulation' --command 'roslaunch tdf_gazebo sarus_simulation_gazebo.launch'");
            system(myCommand.c_str());
        }

        if(!ros::ok())
        {
            return;
        }
    }
    return;
}


