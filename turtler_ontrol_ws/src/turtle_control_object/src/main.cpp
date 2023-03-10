//
// Created by Zwhy2022 on 23-3-1.
//
/** C++ */
#include <iostream>

/** Qt */
#include <QApplication>
#include "widgets.h"
/** Ros */
#include "ros/ros.h"

int main(int argc,char** argv) {
    /** Init node  */
    std::string strNode = "qt_turtle_ctrl";
    ros::init(argc,argv,strNode);
    ros::NodeHandle node;

    /** Pass in the ptr for node */
    QApplication app(argc,argv);

    Widget widget(&node);
    widget.show();

    return app.exec();
}

