#pragma once

//#include <QtWidgets/QWidget>
#include <QMainWindow>
#include "ui_QtApp.h"


#include "MyRobot.h";
#include "GamepadController.h";

#include <QMessageBox>
#include <QAbstractSlider>

class QtApp : public QMainWindow
{
    Q_OBJECT

public:
    QtApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtAppClass ui;
    MyRobot *bot;
    GamepadController *gamepad;

private slots:
    void upButton();
    void downButton();
    void leftButton();
    void rightButton();
    void stopButton();
    void setSpeed(int a);

private:
    int speed = 0;
};
