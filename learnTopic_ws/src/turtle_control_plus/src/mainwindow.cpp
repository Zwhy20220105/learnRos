//
// Created by Zwhy2022 on 23-3-2.
//
// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(ros::NodeHandle *node,QWidget *parent) :
        QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    this->node =node;
    //初始化控件和布局
    initWidgets();

}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::initWidgets() {
    updateTimer = new QTimer(this);
    updateTimer->setInterval(16);
    updateTimer->start();

    connect(updateTimer, &QTimer::timeout, this, &mainwindow::on_timer_update_data);

    //窗体设置
    setWindowTitle("小乌龟控制");
    //设置窗体大小
    resize(400, 120);

    //设置布局
    layout = new QFormLayout();
    this->setLayout(layout);

    //添加输入框
    editLinear = new QLineEdit();
    layout->addRow("线速度", editLinear);

    qDebug().noquote()<<"here: "<<layout->count();

    //添加输入框
    editAngular = new QLineEdit();
    layout->addRow("角速度", editAngular);

    //添加显示
    labelX = new QLabel();
    layout->addRow("当前X坐标", labelX);

    labelY = new QLabel();
    layout->addRow("当前Y坐标", labelY);

    labelLinear = new QLabel();
    layout->addRow("当前线速度", labelLinear);

    labelAngular = new QLabel();
    layout->addRow("当前角速度", labelAngular);

    labelDegrees = new QLabel();
    layout->addRow("当前角度", labelDegrees);

    //添加按钮
    btnSend = new QPushButton("发送");
    layout->addRow(btnSend);

    //添加事件
    btnSend->connect(btnSend, &QPushButton::clicked, this, &mainwindow::on_btn_click_Send);

    //初始化publisher
    std::string topicName = "/turtle1/cmd_vel";
    publisher = node->advertise<geometry_msgs::Twist>(topicName, 1000);

    //初始化subscriber
    std::string poseTopicName = "/turtle1/pose";
    subscriber = node->subscribe(poseTopicName, 1000, &mainwindow::poseCallback, this);
}

void mainwindow::on_timer_update_data()
{
    ros::spinOnce();

    update();

    if (!ros::ok()) {
        close();
    }
}

void mainwindow::on_btn_click_Send()
{
    ROS_DEBUG("打印的内容");
    ROS_INFO("打印的内容");
    ROS_WARN("打印的内容");
    ROS_ERROR("打印的内容");
    ROS_FATAL("打印的内容");

    ROS_DEBUG_STREAM("打印的内容" << "hello");
    ROS_INFO_STREAM("打印的内容" << "hello");
    ROS_WARN_STREAM("打印的内容" << "hello");
    ROS_ERROR_STREAM("打印的内容" << "hello");
    ROS_FATAL_STREAM("打印的内容" << "hello");

    double linearX = editLinear->text().toDouble();
    double angularZ = editAngular->text().toDouble();

    std::cout << "linear.x: " << linearX << std::endl;
    std::cout << "angular.z: " << angularZ << std::endl;

    //创建消息
    geometry_msgs::Twist twist;
    //填充消息
    twist.linear.x = linearX;
    twist.angular.z = angularZ * M_PI / 180;
    //发送消息
    publisher.publish(twist);
}

void mainwindow::poseCallback(const turtlesim::Pose_<std::allocator<void>>::ConstPtr &message) {
    double x = message->x;
    double y = message->y;
    float linear = message->linear_velocity;
    float angular = message->angular_velocity;
    float theta = message->theta;

    labelX->setText(QString::fromStdString(std::to_string(x)));
    labelY->setText(QString::fromStdString(std::to_string(y)));
    labelLinear->setText(QString::fromStdString( std::to_string(linear)));
    labelAngular->setText(QString::fromStdString(std::to_string(angular)));
    labelDegrees->setText(QString::fromStdString(std::to_string(theta * 180 / M_PI)));
}
