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

        connect(this->ui->up, SIGNAL(released()), this, SLOT(stopBot()));
        connect(this->ui->down, SIGNAL(released()), this, SLOT(stopBot()));
        connect(this->ui->left, SIGNAL(released()), this, SLOT(stopBot()));
        connect(this->ui->right, SIGNAL(released()), this, SLOT(stopBot()));

        connect(this->ui->cam_down, SIGNAL(clicked()), this, SLOT(downCamera()));
        connect(this->ui->cam_up, SIGNAL(clicked()), this, SLOT(upCamera()));
        connect(this->ui->cam_left, SIGNAL(clicked()), this, SLOT(leftCamera()));
        connect(this->ui->cam_right, SIGNAL(clicked()), this, SLOT(rightCamera()));

        connect(this->ui->connect, SIGNAL(clicked()), this, SLOT(manageConnexion()));


        // set elements
        this->updateUI(false);


        // start the camera view
        this->ui->View_camera->load(QUrl("http://" + ip + ":8080/?action=stream"));
        this->ui->View_camera->setZoomFactor(1.6);
        this->ui->View_camera->show();


        // start the manager to control the camera
        this->manager = new QNetworkAccessManager();
        QObject::connect(this->manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply* reply) {
                if (reply->error()) {
                    qDebug() << reply->errorString();
                    return;
                }
                QString answer = reply->readAll();
                qDebug() << answer;
            }
        );


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
        if (this->bot->isConnected()) {
            // normal mode, use real values to update UI
            int bot_speed = (int)((float)(this->bot->getSpeed()) * 100.0f / 240.0f);

            this->globalGauge->setValue(bot_speed);
            this->speedGauge->setValue(this->gamepad->getAcceleration());
            this->brakesGauge->setValue(this->gamepad->getBrakes());

            this->distGaugeLeft->setValue(this->bot->getDistLeft());
            this->distGaugeRight->setValue(this->bot->getDistRight());
            this->distGaugeLeft2->setValue(this->bot->getDistLeft2());
            this->distGaugeRight2->setValue(this->bot->getDistRight2());

            this->batterieController->setValue(this->bot->getBattery());
        }
        else {
            // demo mode, use controls to update UI
            int bot_speed = (int)((float)(this->bot->getSpeed()) * 100.0f / 240.0f);

            this->globalGauge->setValue(bot_speed);
            this->speedGauge->setValue(this->gamepad->getAcceleration());
            this->brakesGauge->setValue(this->gamepad->getBrakes());

            int d = -(this->gamepad->getBrakes() - 50) * 2;
            this->distGaugeLeft->setValue(d);
            this->distGaugeRight->setValue(d);
            this->distGaugeLeft2->setValue(d);
            this->distGaugeRight2->setValue(d);

            this->batterieController->setValue(this->gamepad->getAcceleration());
        }
        this->updateUI(this->bot->isConnected());
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

        case Qt::Key_O:
            this->upCamera();
            break;
        case Qt::Key_K:
            this->leftCamera();
            break;
        case Qt::Key_L:
            this->downCamera();
            break;
        case Qt::Key_M:
            this->rightCamera();
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
        bot->setSpeed(240);
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


    // called when the 'up' camera button is pressed
    void UiController::upCamera() {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-100"));
        manager->get(request);
    }

    // called when the 'down' camera button is pressed
    void UiController::downCamera() {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=100"));
        manager->get(request);
    }

    // called when the 'left' camera button is pressed
    void UiController::leftCamera() {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=100"));
        manager->get(request);
    }

    // called when the 'right' camera button is pressed
    void UiController::rightCamera() {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-100"));
        manager->get(request);
    }


    // called when the '<dis>connect' button is pressed
    void UiController::manageConnexion() {
        if (this->bot->isConnected())
            this->bot->disConnect();
        else
            this->bot->doConnect();

        this->updateUI(this->bot->isConnected());
    }

    void UiController::updateUI(bool connected) {
        if (connected) {
            this->ui->connect->setText("Disconnect");
            /*this->ui->camera_container->setVisible(true);
            this->ui->view_disconnected->setVisible(false);*/
        } else {
            this->ui->connect->setText("Connect");
            /*this->ui->camera_container->setVisible(false);
            this->ui->view_disconnected->setVisible(true);*/
        }
        this->ui->camera_container->setVisible(true);
        this->ui->view_disconnected->setVisible(true);
    }
}