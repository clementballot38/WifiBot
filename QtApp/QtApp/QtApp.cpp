#include "QtApp.h"

QtApp::QtApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    bot = new MyRobot(this);
    gamepad = new GamepadController(bot);


    //btn = parent->findChild<QPushButton*>("up");
    //btn = new QPushButton("My Button", this);
    // resize button
    //btn->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(ui.up, SIGNAL(clicked()), this, SLOT(upButton()));
    connect(ui.down, SIGNAL(clicked()), this, SLOT(downButton()));
    connect(ui.left, SIGNAL(clicked()), this, SLOT(leftButton()));
    connect(ui.right, SIGNAL(clicked()), this, SLOT(rightButton()));
    connect(ui.stop, SIGNAL(clicked()), this, SLOT(stopButton()));

    connect(ui.speed_slider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
}


void QtApp::upButton() {
    bot->turn(0);
    bot->setSpeed(speed);
    bot->goForward();
}

void QtApp::downButton() {
    bot->turn(0);
    bot->setSpeed(speed);
    bot->goForward(false);
}

void QtApp::leftButton() {
    bot->turn(-45);
    bot->setSpeed(speed);
    bot->goForward();
}

void QtApp::rightButton() {
    bot->turn(45);
    bot->setSpeed(speed);
    bot->goForward();
}

void QtApp::stopButton() {
    bot->setSpeed(0);
}

void QtApp::setSpeed(int a) {
    speed = a;
    bot->setSpeed(speed);
}