#include "UiController.h"

namespace UiController {
    UiController::UiController(Ui::QtAppClass* _ui)
        : ui(_ui), speed(0) {


        bot = new MyRobot(this);
        gamepad = new GamepadController(bot);


        // boutons
        connect(this->ui->up, SIGNAL(clicked()), this, SLOT(upButton()));
        connect(this->ui->down, SIGNAL(clicked()), this, SLOT(downButton()));
        connect(this->ui->left, SIGNAL(clicked()), this, SLOT(leftButton()));
        connect(this->ui->right, SIGNAL(clicked()), this, SLOT(rightButton()));
        connect(this->ui->stop, SIGNAL(clicked()), this, SLOT(stopButton()));
        
        connect(this->ui->up, SIGNAL(clicked()), this, SLOT(upButton()));
        connect(this->ui->down, SIGNAL(clicked()), this, SLOT(downButton()));
        connect(this->ui->left, SIGNAL(clicked()), this, SLOT(leftButton()));
        connect(this->ui->right, SIGNAL(clicked()), this, SLOT(rightButton()));
        connect(this->ui->stop, SIGNAL(clicked()), this, SLOT(stopButton()));


        //Camera
        this->ui->View_camera->load(QUrl("http://192.168.1.11:8080/?action=stream"));
        this->ui->View_camera->setZoomFactor(1.35);
        this->ui->View_camera->show();

        // gauges
        this->globalGauge = new GaugeController(this);
        this->globalGauge->setMinValue(-100);
        this->speedGauge = new GaugeController(this);
        this->brakesGauge = new GaugeController(this);
        this->distGaugeLeft = new GaugeController(this);
        this->distGaugeRight = new GaugeController(this);
        this->ui->global_gauge->rootContext()->setContextProperty("controller", this->globalGauge);
        this->ui->speed_gauge->rootContext()->setContextProperty("controller", this->speedGauge);
        this->ui->brakes_gauge->rootContext()->setContextProperty("controller", this->brakesGauge);
        this->ui->dist_gauge_left->rootContext()->setContextProperty("controller", this->distGaugeLeft);
        this->ui->dist_gauge_right->rootContext()->setContextProperty("controller", this->distGaugeRight);
        this->gaugesTimer = new QTimer();
        this->gaugesTimer->setInterval(10);
        this->gaugesTimer->start();
        connect(this->gaugesTimer, SIGNAL(timeout()), this, SLOT(updateGauges()));
    }


    void UiController::updateGauges() {
        int bot_speed = (int)((float)(this->bot->getSpeed()) * 100.0f / 240.0f);

        this->globalGauge->setValue(bot_speed);
        this->speedGauge->setValue(this->gamepad->getAcceleration());
        this->brakesGauge->setValue(this->gamepad->getBrakes());
        this->distGaugeLeft->setValue(this->bot->getDistLeft());
        this->distGaugeRight->setValue(this->bot->getDistRight());
    }

    void UiController::keyPressEvent(QKeyEvent* ev) {
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
        }
    }

    void UiController::keyReleaseEvent(QKeyEvent* ev) {
        switch (ev->key()) {
        // Choix de la direction
        case Qt::Key_Z:
        case Qt::Key_S:
        case Qt::Key_Q:
        case Qt::Key_D:
            bot->setSpeed(0);
            break;
        }
    }

    void UiController::upButton() {
        bot->setSpeed(speed);
        bot->goForward();
    }

    void UiController::downButton() {
        bot->setSpeed(speed);
        bot->goForward(false);
    }

    void UiController::leftButton() {
        bot->setSpeed(speed);
        bot->turn(-45);
        bot->goForward();
    }

    void UiController::rightButton() {
        bot->setSpeed(speed);
        bot->turn(45);
        bot->goForward();
    }

    void UiController::stopButton() {
        bot->setSpeed(0);
    }
}