
#include "ros/ros.h"
#include <iostream>
#include "std_msgs/String.h"
#include "Zwhy_msgs/Team.h"

using namespace std;

void topicCallback(const Zwhy_msgs::Team::ConstPtr &msg){
    //cout<<(*msg).data<<endl;
    //cout <<"msg.name: "<< msg->name <<"\t"<<"msg.age: "<<msg->age << endl;

    //输入中文
    cout << msg->name << endl;
    cout << msg->leader.name << endl;
    cout << msg->leader.age << endl;
    cout << msg->intro.data << endl;
    cout << msg->location.linear.x << endl;
    cout << msg->location.linear.y << endl;
    cout << msg->location.linear.z << endl;
    cout << msg->location.angular.x << endl;
    cout << msg->location.angular.y << endl;
    cout << msg->location.angular.z << endl;
    for (auto member : msg->members) {
        cout << member.name << endl;
        cout << member.age << endl;
        cout << "##" << endl;
    }
    cout << "-----------------------" << endl;

}

int main(int argc,char** argv){

    // init node
    string nodeName = "cppSubscriber";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;

    //creat subscriber
    string topicName ="cpptopic";
    const ros::Subscriber& subuscriber= node.subscribe(topicName,1000,topicCallback);
    ros::spin();
    
    return 0;
}
