#include "UiController.h"

namespace UiController {
    UiController::UiController(Ui::QtAppClass* _ui, QString ip)
        : ui(_ui) {


        bot = new MyRobot(this, ip);
        gamepad = new GamepadController(bot);


        // connect the buttons to the events
        connect(this->ui->up, SIGNAL(pressed()), this, SLOT(upButton()));
        connect(this->ui->down, SIGNAL(pressed()), this, SLOT(downButton()));
        connect(this->ui->left, SIGNAL(pressed()), this, SLOT(leftButton()));
        connect(this->ui->right, SIGNAL(pressed()), this, SLOT(rightButton()));

        connect(this->ui->up, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->down, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->left, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->right, SIGNAL(released()), this, SLOT(stopButton()));

        connect(ui->cam_down, SIGNAL(pressed()), this, SLOT(downCamera()));
        connect(ui->cam_up, SIGNAL(pressed()), this, SLOT(upCamera()));
        connect(ui->cam_left, SIGNAL(pressed()), this, SLOT(leftCamera()));
        connect(ui->cam_right, SIGNAL(pressed()), this, SLOT(rightCamera()));


        // start the camera view
        this->ui->View_camera->load(QUrl("http://" + ip + ":8080/?action=stream"));
        this->ui->View_camera->setZoomFactor(1.7);
        this->ui->View_camera->show();


        // connect the gauges to their controller
        this->globalGauge = new GaugeController(this);
        this->globalGauge->setMinValue(-100);
        this->ui->global_gauge->rootContext()->setContextProperty("controller", this->globalGauge);

        this->speedGauge = new GaugeController(this);
        this->ui->speed_gauge->rootContext()->setContextProperty("controller", this->speedGauge);

        this->brakesGauge = new GaugeController(this);
        this->ui->brakes_gauge->rootContext()->setContextProperty("controller", this->brakesGauge);

        this->distGaugeLeft = new GaugeController(this);
        this->ui->dist_gauge_left->rootContext()->setContextProperty("controller", this->distGaugeLeft);

        this->distGaugeRight = new GaugeController(this);
        this->ui->dist_gauge_right->rootContext()->setContextProperty("controller", this->distGaugeRight);
        

        this->distGaugeLeft2 = new GaugeController(this);
        this->ui->dist_gauge_left_2->rootContext()->setContextProperty("controller", this->distGaugeLeft2);

        this->distGaugeRight2 = new GaugeController(this);
        this->ui->dist_gauge_right_2->rootContext()->setContextProperty("controller", this->distGaugeRight2);
        
        this->batterieController = new GaugeController(this);
        this->ui->batterie->rootContext()->setContextProperty("controller", this->batterieController);
        
        
        // start the timer to update the gauges periodically
        this->gaugesTimer = new QTimer();
        this->gaugesTimer->setInterval(10);
        this->gaugesTimer->start();
        connect(this->gaugesTimer, SIGNAL(timeout()), this, SLOT(updateGauges()));
    }


    // update the gauges
    void UiController::updateGauges() {
        int bot_speed = (int)((float)(this->bot->getSpeed()) * 100.0f / 240.0f);

        this->globalGauge->setValue(bot_speed);
        this->speedGauge->setValue(this->gamepad->getAcceleration());
        this->brakesGauge->setValue(this->gamepad->getBrakes());

        this->distGaugeLeft->setValue(this->bot->getDistLeft());
        this->distGaugeRight->setValue(this->bot->getDistRight());
        this->distGaugeLeft2->setValue(this->bot->getDistLeft2());
        this->distGaugeRight2->setValue(this->bot->getDistRight2());
        
        this->batterieController->setValue(bot_speed < 0 ? -bot_speed : 0);
    }


    // called when a key is presses
    void UiController::keyPressEvent(QKeyEvent* ev) {
        switch (ev->key()) {
        case Qt::Key_Z:
            this->upButton();
            break;
        case Qt::Key_S:
            this->downButton();
            break;
        case Qt::Key_Q:
            this->leftButton();
            break;
        case Qt::Key_D:
            this->rightButton();
            break;
      
        }
    }


    // called when a key is released
    void UiController::keyReleaseEvent(QKeyEvent* ev) {
        switch (ev->key()) {
        case Qt::Key_Z:
        case Qt::Key_S:
        case Qt::Key_Q:
        case Qt::Key_D:
            this->stopBot();
            break;
        }
    }


    // called when the 'up' button is presses
    void UiController::upButton() {
        bot->setSpeed(240);
        bot->turn(0);
        bot->goForward();
    }

    // called when the 'down' button is pressed
    void UiController::downButton() {
        bot->setSpeed(24);
        bot->turn(0);
        bot->goForward(false);
    }

    // called when the 'left' button is presses
    void UiController::leftButton() {
        bot->setSpeed(240);
        bot->turn(-45);
        bot->goForward();
    }

    // called when the 'right' button is pressed
    void UiController::rightButton() {
        bot->setSpeed(240);
        bot->turn(45);
        bot->goForward();
    }


    // stops the bot
    void UiController::stopBot() {
        bot->setSpeed(0);
        bot->turn(0);
    }


    void UiController::upCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-100"));
        manager->get(request);
    }
    void UiController::leftCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=100"));
        manager->get(request);
    }
    void UiController::rightCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-100"));
        manager->get(request);
    }
    void UiController::downCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=100"));
        manager->get(request);
    }
}