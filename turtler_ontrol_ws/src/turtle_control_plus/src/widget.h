//
// Created by Zwhy2022 on 23-3-2.
//

#ifndef SRC_MAINWINDOW_H
#define SRC_MAINWINDOW_H

#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(ros::NodeHandle *node,QWidget *parent = nullptr);

    ~Widget() override;
public slots:
    //发送点击事件
    void on_btn_click_Send();

    void on_timer_update_data();

private:
    //初始化控件和布局
    void initWidgets();

    //poseCallback
    void poseCallback(const turtlesim::Pose::ConstPtr &message);

private:
    Ui::widget* ui;

    ros::NodeHandle *node;
    ros::Publisher publisher;
    ros::Subscriber subscriber;

    QTimer* updateTimer;

    //布局
    QFormLayout *layout;
    //线速度输入框
    QLineEdit *editLinear;
    //角速度输入框
    QLineEdit *editAngular;
    // 发送按钮
    QPushButton *btnSend;
    // X坐标
    QLabel *labelX;
    // Y坐标
    QLabel *labelY;
    // 当前线速度
    QLabel *labelLinear;
    // 当前角速度
    QLabel *labelAngular;
    // 当前角度
    QLabel *labelDegrees;
};


#endif //SRC_MAINWINDOW_H
