//
// Created by Zwhy2022 on 23-3-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved
#include "mainwindow.h"


mainWindow::mainWindow(ros::NodeHandle* pNode,QWidget *parent) :QMainWindow(parent){
    this->pNode = pNode;

    /** Layout */
    initWidgets();

    /** Function */
    initFunction();

}

mainWindow::~mainWindow()
{

}

void mainWindow::initWidgets() ///<
{
    setWindowTitle("qt_turtle_control");
    resize(400,120);

    pLayout =new QFormLayout();
    this->setLayout(pLayout);

    pEditLinear = new QLineEdit();
    pLayout->addRow("Linear ",pEditLinear);

    pEditAngular= new QLineEdit();
    pLayout->addRow("Linear ",pEditAngular);

    pSendBtn =new QPushButton("Send");
    pLayout->addRow(pSendBtn);

}

void mainWindow::initFunction() ///<
{
    connect(pSendBtn,&QPushButton::clicked,this, &mainWindow::on_btn_respond_clicked);

    std::string strTopic = "/turtle1/cmd_vel";
    publisher = pNode->advertise<geometry_msgs::Twist>(strTopic,1000);
}


void mainWindow::on_btn_respond_clicked() ///<
{
    /** get data from widgets */
    double  linearX =pEditLinear->text().toDouble();
    double  angularZ =pEditAngular->text().toDouble();

    std::cout << "linear.x" << linearX <<std::endl;
    std::cout << "angular.z" << angularZ <<std::endl;

    geometry_msgs::Twist  twist;

    twist.linear.x = linearX;
    twist.angular.x = angularZ* M_PI/180;

    publisher.publish(twist);

    //test ssh

}

