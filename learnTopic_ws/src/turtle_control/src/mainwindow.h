/**
 *
 */
#ifndef TURTLE_CONTROL_MAINWINDOW_H
#define TURTLE_CONTROL_MAINWINDOW_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
/** C++ */
#include <iostream>

/** Ros */
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

/** Qt */
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

class mainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit mainWindow(ros::NodeHandle* pNode, QWidget* parent = nullptr);

    ~mainWindow() override;

private:

    void initWidgets();

    void initFunction();


public slots:
    void on_btn_respond_clicked();

private:
    /** Ros */
    ros::NodeHandle* pNode;
    ros::Publisher publisher;

    /** Layout */
    QFormLayout* pLayout;
    QLineEdit* pEditLinear;
    QLineEdit* pEditAngular;
    QPushButton* pSendBtn;

};


#endif //TURTLE_CONTROL_MAINWINDOW_H
