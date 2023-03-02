//
// Created by Zwhy2022 on 23-3-1.
//
/** C++ */
#include <iostream>

/** Qt */
#include <QApplication>

/** Ros */
#include "ros/ros.h"


int main(int argc,char** argv)
{
    /** Init node  */
    std::string strNode = "qt_turtle_ctrl";
    ros::init(argc,argv,strNode);

    QApplication app(argc,argv);


    return app.exec();
}

