//
// Created by Zwhy2022 on 23-3-3.
//
#include <iostream>

#include "ros/ros.h"
#include "roscpp_tutorials/TwoInts.h"

int main(int argc, char **argv)
{
    //初始化节点
    std::string nodeName = "service_client";
    ros::init(argc, argv, nodeName);
    //创建节点
    ros::NodeHandle node;

    //创建Service Client
    std::string serviceName = "service";
    ros::ServiceClient client = node.serviceClient<roscpp_tutorials::TwoInts>(serviceName);

    // 创建Service
    roscpp_tutorials::TwoInts service;
    service.request.a = 10;
    service.request.b = 15;

    //发送请求
    client.call(service);
    //获取响应结果
    ROS_INFO_STREAM("response result: " << service.response.sum);
    //阻塞
    ros::spin();
    return 0;
}
