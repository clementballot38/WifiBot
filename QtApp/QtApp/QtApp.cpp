#include "QtApp.h"

QtApp::QtApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    bot = new MyRobot(this);


    //btn = parent->findChild<QPushButton*>("up");
   // btn = new QPushButton("My Button", this);
     //resize button
    //btn->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(ui.up, SIGNAL(clicked()), this, SLOT(upButton()));
    connect(ui.down, SIGNAL(clicked()), this, SLOT(downButton()));
    connect(ui.left, SIGNAL(clicked()), this, SLOT(leftButton()));
    connect(ui.right, SIGNAL(clicked()), this, SLOT(rightButton()));
    connect(ui.stop, SIGNAL(clicked()), this, SLOT(stopButton()));

    //connect(ui.speed_slider, SIGNAL(valueChanged()), this, SLOT(setSpeed(int)));

    //Caemra
    ui.View_camera->load(QUrl("http://192.168.1.11:8080/?action=stream"));
    ui.View_camera->setZoomFactor(1.52);
    ui.View_camera->show();
    
   
   
   
    


}
        
void QtApp::keyPressEvent(QKeyEvent* ev) {
    switch (ev->key()) {
        // Choix de la direction
    case Qt::Key_Z:
        bot->createData(100, 100, true);

        break;
    case Qt::Key_S:
        bot->createData(100, 100, false);
        break;
    case Qt::Key_Q:
        bot->createData(0, 100, true);
        break;
    case Qt::Key_D:
        bot->createData(100, 0, true);
        break;
    case Qt::Key_W:
        bot->createData(0, 0, true);
        break;

    }
}

void QtApp::keyReleaseEvent(QKeyEvent* ev) {
    switch (ev->key()) {
        // Choix de la direction
    case Qt::Key_Z:
        bot->createData(0, 0, 0);

        break;
    case Qt::Key_S:
        bot->createData(0, 0, 0);
        break;
    case Qt::Key_Q:
        bot->createData(0, 0, 0);
        break;
    case Qt::Key_D:
        bot->createData(0, 0, 0);
        break;
    case Qt::Key_W:
        bot->createData(0, 0, 0);
        break;

    }
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