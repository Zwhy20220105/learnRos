//
// Created by Zwhy2022 on 23-3-2.
//
#include <iostream>
#include "ros/ros.h"
#include "roscpp_tutorials/TwoInts.h"
//#include "option_srvs/NumOption.h"

bool callback(roscpp_tutorials::TwoInts::Request &request,roscpp_tutorials::TwoInts::Response& response)
{
    /** request */
    long a = request.a;
    long b = request.b;
    /** response */
    response.sum = a + b;

    return true;
}

int main(int argc,char** argv)///<
{
    /** init node */
    std::string strNode = "cpp_server_node";
    ros::init(argc,argv,strNode);
    ros::NodeHandle node;

    /** create service server */
    std::string strService = "service";
    const ros::ServiceServer& server =node.advertiseService(strService,callback);

    ros::spin();
    return 0;

}
