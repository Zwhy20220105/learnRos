//
// Created by Zwhy2022 on 23-3-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainwindow.h"

mainWindow::mainWindow(ros::NodeHandle* pNode,QWidget *parent) :QMainWindow(parent){
    this->pNode = pNode;

    /** Init */
    initWidgets();
}

mainWindow::~mainWindow()
{

}

void mainWindow::initWidgets() ///<
{
    setWindowTitle("qt_turtle_control");
    resize(400,120);




}
