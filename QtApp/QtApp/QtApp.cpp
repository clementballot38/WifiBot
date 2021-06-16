#include "QtApp.h"

namespace QtApp {
    QtApp::QtApp(QWidget* parent)
        : QMainWindow(parent), speed(0) {
    
        
        ui.setupUi(this);

        bot = new MyRobot(this);
        gamepad = new GamepadController(bot);


        connect(ui.up, SIGNAL(pressed()), this, SLOT(upButton()));
        connect(ui.down, SIGNAL(pressed()), this, SLOT(downButton()));
        connect(ui.left, SIGNAL(pressed()), this, SLOT(leftButton()));
        connect(ui.right, SIGNAL(pressed()), this, SLOT(rightButton()));
       
       
        connect(ui.up, SIGNAL(released()), this, SLOT(stopButton()));
        connect(ui.down, SIGNAL(released()), this, SLOT(stopButton()));
        connect(ui.left, SIGNAL(released()), this, SLOT(stopButton()));
        connect(ui.right, SIGNAL(released()), this, SLOT(stopButton()));
       



        connect(ui.cam_down, SIGNAL(pressed()), this, SLOT(downCamera()));
        connect(ui.cam_up, SIGNAL(pressed()), this, SLOT(upCamera()));
        connect(ui.cam_left, SIGNAL(pressed()), this, SLOT(leftCamera()));
        connect(ui.cam_right, SIGNAL(pressed()), this, SLOT(rightCamera()));
        //connect(ui.speed_slider, SIGNAL(valueChanged()), this, SLOT(setSpeed(int)));


        //Camera
        ui.View_camera->load(QUrl("http://192.168.1.11:8080/?action=stream"));
       
     

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




      


     

      


        ui.View_camera->setZoomFactor(1.52);
        ui.View_camera->show();

        //Batterie
       
        QObject::connect(this, SIGNAL(updateUI(QByteArray)), ui.progressBar, SLOT(maj_batterie()));
        ui.progressBar->setValue(bot->getBattery());
        qDebug() << bot->getBattery() << " pourcentage ";
    }
        //controle clavier
    void QtApp::keyPressEvent(QKeyEvent* ev) {
        switch (ev->key()) {
        // Choix de la direction
        case Qt::Key_Z:
            bot->setSpeed(240);
            bot->goForward(false);
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
        case Qt::Key_F:
            //déplacement caméra gauche
            request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=100"));
            manager->get(request);

            break;

        case Qt::Key_H:
            //déplacement caméra droite
            request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-100"));
            manager->get(request);

            break;
        case Qt::Key_T:

            //déplacement caméra haut
            request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-100"));
            manager->get(request);

            break;



        case Qt::Key_G:

            //déplacement caméra bas
            request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=100"));
            manager->get(request);

            break;



        }
    }
    //Fonction release
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
        bot->setSpeed(240);
        qDebug() << "up";
        bot->goForward();
    }

    void QtApp::downButton() {
        bot->setSpeed(240);
        bot->goForward(false);
    }

    void QtApp::leftButton() {
        bot->setSpeed(240);
        bot->turn(-45);
        bot->goForward();
    }

    void QtApp::rightButton() {
        bot->setSpeed(240);
        bot->turn(45);
        bot->goForward();
    }

    void QtApp::stopButton() {
        bot->setSpeed(0);
        qDebug() << "stop";
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
   



    //Batterie

    void QtApp::battStatusChanged(int percent)
    {
        QString c = "green";
        if (percent < 30)
            c = "yellow";
        else if (percent < 10)
            c = "red";
        
        

        QString myStyleSheet = QString(" QProgressBar::chunk { background: %1; }").arg(c);

        ui.progressBar->setStyleSheet("background-color:black;");
        ui.progressBar->setValue(percent);

    }


    void QtApp::downCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=100"));
        manager->get(request);
    }

    void QtApp::upCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-100"));
        manager->get(request);
    }
    void QtApp::leftCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=100"));
        manager->get(request);
    }
    void QtApp::rightCamera()
    {
        request.setUrl(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-100"));
        manager->get(request);
    }













}