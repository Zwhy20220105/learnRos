//
// Created by Zwhy2022 on 23-3-2.
//
#include <iostream>
#include "ros/ros.h"
#include "roscpp_tutorials/TwoInts.h"
//#include "option_srvs/NumOption.h"

/** catkin_make */
//#include "option_srvs/NumOption.h"
/** clion make */
#include "../../../devel/include/option_srvs/NumOption.h"

/** myself explore*/
//#include "/home/zwhy2022/learnRos/service_ws/devel/include/option_srvs/NumOption.h"

bool callback(option_srvs::NumOption::Request &request,option_srvs::NumOption::Response& response)
{
    /** request */
    float a = request.a;
    float b = request.b;
    std::string strOption =request.option;
    /** response */
    if (strOption.size()==1) {
        const char*  cOption = strOption.c_str();
        switch (*cOption) {
            case '+':
                response.result = a + b;
                break;
            case '-':
                response.result = a - b;
                break;
            case '*':
                response.result = a * b;
                break;
            case '/':
                if (b!=0)
                {
                    response.result = a / b;
                }
                else{
                    return false;
                }
                break;
            case '%':
                response.result = (int)a % (int)b;
                break;
        }
        return true;
    }else
    {
        return false;
    }
    return true;
}

int main(int argc,char** argv)///<
{
    /** init node */
    std::string strNode = "service_server";
    ros::init(argc,argv,strNode);
    ros::NodeHandle node;

    /** create service server */
    std::string strService = "service";
    const ros::ServiceServer& server =node.advertiseService(strService,callback);

    ros::spin();
    return 0;

}
