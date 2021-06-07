#include "QtApp.h"

namespace QtApp {
    QtApp::QtApp(QWidget* parent)
        : QMainWindow(parent), speed(0) {
    
        
        ui.setupUi(this);

        bot = new MyRobot(this);
        gamepad = new GamepadController(bot);


        connect(ui.up, SIGNAL(clicked()), this, SLOT(upButton()));
        connect(ui.down, SIGNAL(clicked()), this, SLOT(downButton()));
        connect(ui.left, SIGNAL(clicked()), this, SLOT(leftButton()));
        connect(ui.right, SIGNAL(clicked()), this, SLOT(rightButton()));
        connect(ui.stop, SIGNAL(clicked()), this, SLOT(stopButton()));


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
            bot->setSpeed(240);
            bot->goForward();
            break;
        case Qt::Key_S:
            bot->setSpeed(240);
            bot->goForward(false);
            break;
        case Qt::Key_Q:
            bot->setSpeed(240);
            bot->turn(-45);
            bot->goForward();
            break;
        case Qt::Key_D:
            bot->setSpeed(240);
            bot->turn(45);
            bot->goForward();
            break;
        case Qt::Key_W:
            bot->setSpeed(0);
            break;
        }
    }

    void QtApp::keyReleaseEvent(QKeyEvent* ev) {
        switch (ev->key()) {
        // Choix de la direction
        case Qt::Key_Z:
        case Qt::Key_S:
        case Qt::Key_Q:
        case Qt::Key_D:
        case Qt::Key_W:
            bot->setSpeed(0);
            break;
        }
    }








    void QtApp::upButton() {
        bot->setSpeed(speed);
        bot->goForward();
    }

    void QtApp::downButton() {
        bot->setSpeed(speed);
        bot->goForward(false);
    }

    void QtApp::leftButton() {
        bot->setSpeed(speed);
        bot->turn(-45);
        bot->goForward();
    }

    void QtApp::rightButton() {
        bot->setSpeed(speed);
        bot->turn(45);
        bot->goForward();
    }

    void QtApp::stopButton() {
        bot->setSpeed(0);
    }

    void QtApp::setSpeed(int val) {
        speed = 0;
        std::cout << val << std::endl;
        //std::cout << "Speed : " << speed << std::endl;
        bot->setSpeed(speed);
    }

    void QtApp::updateMovement(int speed, Direction dir, bool forward) {
        switch (dir) {
        case Direction::left :
            //bot->createData(speed / (forward ? 3 : 1), speed / (forward ? 1 : 3), forward);
            break;
        case Direction::straight :
            //bot->createData(speed, speed, forward);
            break;
        case Direction::right :
            //bot->createData(speed / (forward ? 1 : 3), speed / (forward ? 3 : 1), forward);
            break;
        }
    }
}