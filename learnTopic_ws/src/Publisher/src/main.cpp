//
// Created by zwhy2022 on 2/28/23.

#include "ros/ros.h"
#include <iostream>
#include "std_msgs/String.h"
#include "Zwhy_msgs/Zwhy.h"
#include "Zwhy_msgs/Team.h"

using namespace std;

int main(int argc, char **argv) {

    // nodeName->ros::init()->[rosNode]->node.advertise();
    //Init ros
    string nodeName = "cppPublisher";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //Create a publisher through a node
    string topicName = "cpptopic";
    const ros::Publisher &publisher = node.advertise<Zwhy_msgs::Team>(topicName, 1000);
    //const ros::Publisher &publisher = node.advertise<std_msgs::String>(topicName, 1000);

    //Publish messages according tp a certain period
    int index = 0;
    ros::Rate rate(1);
    while (ros::ok()) {

        Zwhy_msgs::Team Team;
        Team.name = "jz";
        Team.leader.name = "zj";;
        Team.leader.age = index;
        Team.intro.data = "agv or amr";
        Team.location.linear.x = index;
        Team.location.linear.y = index;
        Team.location.linear.z = index;
        Team.location.angular.x = index;
        Team.location.angular.y = index;
        Team.location.angular.z = index;

        for (int i = 0; i < 3; ++i) {
            Zwhy_msgs::Zwhy stu;
            stu.name = "stu_" + to_string(index) + "_"+ to_string(i);
            stu.age = i;
            Team.members.emplace_back(stu);
        }


        //std_msgs::String msg;
        //msg.data = "hello pub " + to_string(index);
        publisher.publish(Team);
        //cout <<"msg.name: "<< msg->name <<"\t"<<"msg.age: "<<msg->age << endl;
        cout << Team<<endl;
        index++;
        rate.sleep();
    }
    ros::spin();
    
    return 0;
}