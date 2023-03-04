
#if true
#include <iostream>
#include "ros/ros.h"
int main(int argc, char **argv) {
    // init ros
    std::string nodeName = "hello_cpp";
    ros::init(argc, argv, nodeName);

    // creat node
    ros::NodeHandle node;
    //fps operate
    ros::Rate rate(10);
    while (ros::ok()) {
        std::cout << "hello ros cpp node" << std::endl;
        rate.sleep();
    }

    //Blcking threads
    ros::spin();
    return 0;
}
#endif

// undo
#if false
#include "ros/ros.h"
#include <iostream>
#include "std_msgs/String.h"

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "cpppublisher";
    string topicName = "cpptopic";

    //Init ros
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //Create a publisher through a node
    const ros::Publisher &publisher = node.advertise<std_msgs::String>(topicName, 1000);

    //Publish messages according tp a certain period
    int index = 0;
    ros::Rate rate(1);
    while (ros::ok()) {
        std_msgs::String msg;
        msg.data = "hello pub " + to_string(index);
        publisher.publish(msg);

        cout << msg.data << endl;

        rate.sleep();
        index++;
    }
    return 0;
}

#endif
