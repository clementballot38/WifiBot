#pragma once

//#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <iostream>
#include "ui_QtApp.h"


#include "MyRobot.h";
#include "GamepadController.h";

#include <QMessageBox>
namespace QtApp {
    enum class Direction { left = 0, straight = 1, right = 2 };


    class QtApp : public QMainWindow
    {
        Q_OBJECT

    public:
        QtApp(QWidget* parent = Q_NULLPTR);

    private:
        Ui::QtAppClass ui;
        MyRobot* bot;
        void updateMovement(int speed, Direction dir, bool forward);
        int speed;

    private slots:
        void upButton();
        void downButton();
        void leftButton();
        void rightButton();
        void stopButton();
        void setSpeed();
    };
}