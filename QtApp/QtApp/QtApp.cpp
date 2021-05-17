#include "QtApp.h"

QtApp::QtApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    bot = new MyRobot(this);


    //btn = parent->findChild<QPushButton*>("up");
    btn = new QPushButton("My Button", this);
    // resize button
    btn->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(ui.up, SIGNAL(clicked()), this, SLOT(upButton()));
}


void QtApp::upButton() {
    bot->send(100, 10, true);
}