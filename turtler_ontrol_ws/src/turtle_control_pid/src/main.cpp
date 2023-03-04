#include <iostream>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include "ros/ros.h"

#include "QApplication"
#include "QtWidgets"

using namespace std;

double distX,distY;
double srcX,srcY;

void clickDone(QLineEdit *xEdit, QLineEdit *yEdit) {
    distX = xEdit->text().toDouble();
    distY = yEdit->text().toDouble();
    ROS_INFO_STREAM("distX: " << distX << "  distY:" << distY);
}

void poseCallback(const turtlesim::Pose::ConstPtr &msg) {
    ROS_INFO_STREAM("x: " << msg->x);
    ROS_INFO_STREAM("y: " << msg->y);

    srcX = msg->x;
    srcY = msg->y;

    ROS_INFO_STREAM("theta: " << msg->theta);
    ROS_INFO_STREAM("linear: " << msg->linear_velocity);
    ROS_INFO_STREAM("angular: " << msg->angular_velocity);
    ROS_INFO_STREAM("degrees: " << msg->theta * 180 / M_PI);
    ROS_INFO_STREAM("=========================================");

    // 更新当前姿态坐标信息
    QLabel *xLb = new QLabel(QString::number(msg->x));
    QLabel *yLb = new QLabel(QString::number(msg->y));
    QLabel *thetaLb = new QLabel(QString::number(msg->theta));
    xLb->setAlignment(Qt::AlignRight);
    yLb->setAlignment(Qt::AlignRight);
    thetaLb->setAlignment(Qt::AlignRight);
    qDeleteAll(((QHBoxLayout*) xLb->parent())->findChildren<QLabel*>());
    ((QFormLayout*) xLb->parent())->addRow("x坐标", xLb);
    ((QFormLayout*) yLb->parent())->addRow("y坐标", yLb);
    ((QFormLayout*) thetaLb->parent())->addRow("角度", thetaLb);

}

double calcDistance(double srcX, double srcY, double distX, double distY) {
    double deltaX = distX - srcX;
    double deltaY = distY - srcY;
    /** 平方开根号 */
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

int main(int argc, char **argv) {

    string nodeName = "turtle_control";

    // 创建节点
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    // 创建Qt程序
    QApplication app(argc, argv);
    //窗体
    QWidget window;
    window.setWindowTitle("小乌龟控制器");
    window.resize(400, 0);
    //布局
    QFormLayout layout;
    /** reference? no! get addr */
    window.setLayout(&layout);

    // 目标x坐标
    QLineEdit xEdit("10.54444");
    layout.addRow("x坐标", &xEdit);

    // 目标y坐标
    QLineEdit yEdit("5.54444");
    layout.addRow("y坐标", &yEdit);

    //当前姿态坐标信息
    QHBoxLayout poseLayout;
    layout.addRow(&poseLayout);

    QFormLayout xLayout;
    QLabel xLb;
    xLayout.addRow("x坐标", &xLb);
    poseLayout.addLayout(&xLayout);

    QFormLayout yLayout;
    QLabel yLb;
    yLayout.addRow("y坐标", &yLb);
    poseLayout.addLayout(&yLayout);

    QFormLayout thetaLayout;
    QLabel thetaLb;
    thetaLayout.addRow("角度", &thetaLb);
    poseLayout.addLayout(&thetaLayout);

    // 执行按钮
    QPushButton btnDone("执行");
    layout.addRow(&btnDone);

    // 事件设置
    /** 这个手法有点高级 */
    /** 之前会这个bind 就可以代替lanbada表达式了 */
    btnDone.connect(&btnDone, &QPushButton::clicked,bind(&clickDone, &xEdit, &yEdit));
    //btnDone.connect(&btnDone, &QPushButton::clicked,&btnDone,bind(&clickDone, &xEdit, &yEdit));


    //小乌龟控制地址
    string velTopicName = "/turtle1/cmd_vel";
    //小乌龟数据获得
    string poseTopicName = "/turtle1/pose";
    // 创建小乌龟移动发布者
    ros::Publisher &&publisher = node.advertise<geometry_msgs::Twist>(velTopicName, 1000);
    // 创建小乌龟位置的订阅者
    const ros::Subscriber &subscriber = node.subscribe(poseTopicName, 1000, poseCallback);


    ros::Rate rate(1);
    while (calcDistance(srcX, srcY, distX, distY) > 0.1) {
        // 获取srcX，srcY
        srcX = pose->x;
        srcY = pose->y;

        //计算当前距离目标点的距离
        double linearDistance = calcDistance(srcX, srcY, distX, distY);
        //计算剩下了的平均速度
        double linearTargetVel = linearDistance / time;

        /** p */
        double linearError = linearTargetVel - linearVel;

        /** i */
        linearTotalError += linearError;

        /** d */
        double linearDeltaError = linearError - linearLastError;
        linearLastError = linearError;

        //设置速度
        geometry_msgs::Twist twist;
        twist.linear.x = linearVel;
        twist.angular.z = 0;
        publisher.publish(twist);
        rate.sleep();
    }





    window.show();

    return app.exec();
}