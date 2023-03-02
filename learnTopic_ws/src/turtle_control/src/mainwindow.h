/**
 *
 */
#ifndef TURTLE_CONTROL_MAINWINDOW_H
#define TURTLE_CONTROL_MAINWINDOW_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
/** Ros */
#include "ros/ros.h"
/** Qt */
#include "QFormLayout"
#include <QLineEdit>
class mainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit mainWindow(ros::NodeHandle* pNode, QWidget* parent = nullptr);

    ~mainWindow() override;

private:

    void initWidgets();


private:
    /** Ros */
    ros::NodeHandle* pNode;
    ros::Publisher publisher;

    /** Layout */
    QFormLayout* layout;
    QLineEdit* editLinear;

};


#endif //TURTLE_CONTROL_MAINWINDOW_H
