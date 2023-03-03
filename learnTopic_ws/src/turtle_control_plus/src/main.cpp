//
// Created by Zwhy2022 on 23-3-2.
//

#include <iostream>
#include "ros/ros.h"
#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char **argv) {
    string nodeName = "turtle_ctrl2";
    //创建节点
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //开启一个异步的轮询器
    ros::AsyncSpinner spinner(1);
    spinner.start();

    //Qt程序添加
    QApplication app(argc, argv);

    //创建窗体
    mainwindow window(&node);


    window.show();
    return app.exec();
}
