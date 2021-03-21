#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <QTimer>
#include <QTime>
#include <QString>
#include "geometry_msgs/TwistStamped.h"


TestPluginWidget::TestPluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPluginWidget)
{
    ui->setupUi(this);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(Update_Display()));
    timer_1s->start(500);

    std::string drone;
    for(int i=0; i<num_Drones; i++){
        drone = std::to_string(i);
        ui->comboBox->addItem(drone.c_str());
    }
}

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here
    delete ui;
}

void TestPluginWidget::Update_Display() {
    std::string speed;

    QString currentDron;
    currentDron.sprintf("%d", ui->comboBox->currentIndex());
    if(currentDron.toInt() == 1){
        speed = std::to_string(dronSpeed_x);
        ui->speedxText->setText(speed.c_str());
    }
    else {
        speed = std::to_string(dronSpeed_y);
        ui->speedyText->setText(speed.c_str());
    }
}


void TestPluginWidget::ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx){
    this->dronSpeed_x = vx->twist.linear.x;
}

void TestPluginWidget::ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy){
    this->dronSpeed_y = vy->twist.linear.y;
}

void TestPluginWidget::init_ROS_Node()
{
    // Write initialization code here

    // PUBLISHERS
    buttonPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);

    // SUBSCRIBERS
    speedx = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speedx_callback, this);
    speedy = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speedy_callback, this);
}

void TestPluginWidget::on_pushButton_clicked()
{
    // Button clicked callback
    std_msgs::String message;
    message.data = "Hello World!";
    buttonPublisher.publish(message);
    ui->pubText->setText(message.data.c_str());
}
