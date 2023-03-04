/** C++ */
#include <iostream>

/** Qt */
#include <QApplication>
#include <QtWidgets>
/** Ros */
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

QLineEdit* editLinear;
QLineEdit* editDegrees;
QPushButton* sendBtn;

const ros::Publisher *publisherPtr;

void clickedBtn()
{
    /** Get data from lineEdit */
    double linearX = editLinear->text().toDouble();
    double angularZ =editDegrees->text().toDouble();

    /** Gush data to "msgBox" */
    geometry_msgs::Twist tTwist;
    tTwist.linear.x = linearX;
    tTwist.angular.z= angularZ * M_PI/180;

    publisherPtr->publish(tTwist);
}

int main(int argc, char *argv[])
{
    /** Init ros,node */
    std::string nodeName = "qt_turtle_ctrl";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;

    /** Create publisher form node */
    std::string strTopic = "/turtle1/cmd_vel";
    const ros::Publisher& publisher = node.advertise<geometry_msgs::Twist>(strTopic,1000);
    publisherPtr = &publisher;  ///< note:  get addr

    /** create QWindow */
    QApplication app(argc,argv);
    QWidget widget;
    widget.resize(400,0);
    widget.setWindowTitle("qt_turtle_ctrl");

    QFormLayout* layout = new QFormLayout();
    widget.setLayout(layout);

    editLinear = new QLineEdit();
    editLinear->setText("0.0");
    layout->addRow("Linear",editLinear);

    editDegrees = new QLineEdit();
    editDegrees->setText("0.0");
    layout->addRow("Degrees",editDegrees);

    sendBtn = new QPushButton("send");
    layout->addRow(sendBtn);

    widget.show();

    sendBtn->connect(sendBtn,&QPushButton::clicked,&widget,clickedBtn);

    return app.exec();

}
