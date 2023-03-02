
#ifndef TURTLE_CONTROL_MAINWINDOW_H
#define TURTLE_CONTROL_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

#include "ros/ros.h"

class mainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit mainWindow(ros::NodeHandle* pNode, QWidget* parent = nullptr);

    ~mainWindow() override;

private:

    void initWidgets();


private:
    ros::NodeHandle* pNode;

};


#endif //TURTLE_CONTROL_MAINWINDOW_H
