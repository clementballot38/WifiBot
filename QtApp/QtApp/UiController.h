#pragma once

#include <QMediaPlayer>
#include <QtWidgets>
#include <QtWebEngineWidgets>
#include <QMessageBox>
#include <ui_QtApp.h>
#include <QTimer>
#include <QNetworkRequest>
#include "MyRobot.h";
#include "GamepadController.h";
#include "GaugeController.h";



namespace UiController {
    enum class Direction { left = 0, straight = 1, right = 2 };


    class UiController : public QObject
    {
       Q_OBJECT



    public:
        UiController(Ui::QtAppClass* _ui);
        int speed;

    

    private:
        QTimer* gaugesTimer;
        Ui::QtAppClass* ui;
        MyRobot* bot;
        GamepadController* gamepad;
        GaugeController *speedGauge, *brakesGauge, *distGaugeLeft, *distGaugeRight, *batterieController;
        void keyPressEvent(QKeyEvent* ev);
        void keyReleaseEvent(QKeyEvent* ev);
        QNetworkAccessManager* Camera;
        QNetworkRequest request;
        QNetworkAccessManager* manager;
    private slots:
        void upButton();
        void downButton();
        void leftButton();
        void rightButton();
        void stopButton();
        void updateGauges();
        void downCamera();
        void upCamera();
        void leftCamera();
        void rightCamera();
    };
}