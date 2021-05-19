#include "QtApp.h"

QtApp::QtApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    bot = new MyRobot(this);


    //btn = parent->findChild<QPushButton*>("up");
    //btn = new QPushButton("My Button", this);
    // resize button
    //btn->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(ui.up, SIGNAL(clicked()), this, SLOT(upButton()));
    connect(ui.down, SIGNAL(clicked()), this, SLOT(downButton()));
    connect(ui.left, SIGNAL(clicked()), this, SLOT(leftButton()));
    connect(ui.right, SIGNAL(clicked()), this, SLOT(rightButton()));
    connect(ui.stop, SIGNAL(clicked()), this, SLOT(stopButton()));
}


void QtApp::upButton() {
    bot->createData(100, 100, true);
}

void QtApp::downButton() {
    bot->createData(100, 100, false);
}

void QtApp::leftButton() {
    bot->createData(0, 100, true);
}

void QtApp::rightButton() {
    bot->createData(100, 0, true);
}

void QtApp::stopButton() {
    bot->createData(0, 0, true);
}