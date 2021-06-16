#include "UiController.h"

namespace UiController {
    UiController::UiController(Ui::QtAppClass* _ui)
        : ui(_ui), speed(0) {


        bot = new MyRobot(this);
        gamepad = new GamepadController(bot);


        // boutons
        connect(this->ui->up, SIGNAL(pressed()), this, SLOT(upButton()));
        connect(this->ui->down, SIGNAL(pressed()), this, SLOT(downButton()));
        connect(this->ui->left, SIGNAL(pressed()), this, SLOT(leftButton()));
        connect(this->ui->right, SIGNAL(pressed()), this, SLOT(rightButton()));

        connect(this->ui->up, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->down, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->left, SIGNAL(released()), this, SLOT(stopButton()));
        connect(this->ui->right, SIGNAL(released()), this, SLOT(stopButton()));


        //Camera
        this->ui->View_camera->load(QUrl("http://192.168.1.11:8080/?action=stream"));
        this->ui->View_camera->setZoomFactor(1.35);
        this->ui->View_camera->show();


        //manager
        manager = new QNetworkAccessManager();
        QObject::connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply* reply) {
                if (reply->error()) {
                    qDebug() << reply->errorString();
                    return;
                }

                QString answer = reply->readAll();

                qDebug() << answer;
            }
        );



        //Camera
        connect(ui->cam_down, SIGNAL(pressed()), this, SLOT(downCamera()));
        connect(ui->cam_up, SIGNAL(pressed()), this, SLOT(upCamera()));
        connect(ui->cam_left, SIGNAL(pressed()), this, SLOT(leftCamera()));
        connect(ui->cam_right, SIGNAL(pressed()), this, SLOT(rightCamera()));

        // gauges
        this->speedGauge = new GaugeController(this);
        this->brakesGauge = new GaugeController(this);
        this->distGaugeLeft = new GaugeController(this);
        this->distGaugeRight = new GaugeController(this);
        this->batterieController = new GaugeController(this);
        this->ui->speed_gauge->rootContext()->setContextProperty("controller", this->speedGauge);
        this->ui->brakes_gauge->rootContext()->setContextProperty("controller", this->brakesGauge);
        this->ui->dist_gauge_left->rootContext()->setContextProperty("controller", this->distGaugeLeft);
        this->ui->dist_gauge_right->rootContext()->setContextProperty("controller", this->distGaugeRight);
        this->ui->batterie->rootContext()->setContextProperty("controller", this->batterieController);
        this->gaugesTimer = new QTimer();
        
        this->gaugesTimer->setInterval(10);
        this->gaugesTimer->start();
        connect(this->gaugesTimer, SIGNAL(timeout()), this, SLOT(updateGauges()));
    }


    void UiController::updateGauges() {
        int bot_speed = (int)((float)(this->bot->getSpeed()) * 100.0f / 240.0f);

        this->speedGauge->setValue(bot_speed > 0 ? bot_speed : 0);
        this->brakesGauge->setValue(bot_speed < 0 ? -bot_speed : 0);
        this->distGaugeLeft->setValue(this->bot->getDistLeft());
        this->distGaugeRight->setValue(this->bot->getDistRight());
        this->batterieController->setValue(bot_speed < 0 ? -bot_speed : 0);
        qDebug() << this->bot->getDistLeft() << " " << this->bot->getDistRight();
        //this->distGauge->setValue(bot_speed > 0 ? bot_speed : 0);
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
        qDebug() << "up";
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