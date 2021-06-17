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



/*
 * UiController class
 * -----------------------
 *
 * This class controls the attached UI :
 *      - gauges
 *      - buttons
 *      - camera view
 *      - keyboard controls
 */



namespace UiController {
    enum class Direction { left = 0, straight = 1, right = 2 }; // available directions


    class UiController : public QObject
    {
       Q_OBJECT


    public:
        UiController(Ui::QtAppClass* _ui, QString _ip);  // constructor
        void keyPressEvent(QKeyEvent* ev);               // override the QObject keyPress event to handle keyboard controls
        void keyReleaseEvent(QKeyEvent* ev);             // override the QObject keyRelease event to handle keyboard controls


    private:
        QString ip;                             // bot's IP adress
        QTimer* gaugesTimer;                    // timer used to update the gauges periodically
        Ui::QtAppClass* ui;                     // attached UI
        MyRobot* bot;                           // attached bot
        GamepadController* gamepad;             // attached gamepad
        void updateUI(bool connected);          // updates visible elements & button text
        QNetworkRequest request;                // requests sent to the bot's camera
        QNetworkAccessManager* manager;         // manages the requests sent to the bot's camera
        GaugeController* globalGauge, * speedGauge, * brakesGauge, * distGaugeLeft, * distGaugeRight, * distGaugeLeft2, * distGaugeRight2, * batterieController;    // attached gauges


    private slots:
        void upButton();        // called when the 'up' button is pressed
        void downButton();      // called when the 'down' button is pressed
        void leftButton();      // called when the 'left' button is pressed
        void rightButton();     // called when the 'right' button is pressed
        void stopBot();         // stops the bot
        void updateGauges();    // called when the gauges are updated
        void upCamera();        // called when the 'up' camera button is pressed
        void downCamera();      // called when the 'down' camera button is pressed
        void leftCamera();      // called when the 'left' camera button is pressed
        void rightCamera();     // called when the 'right' camera button is pressed
        void manageConnexion(); // called when the '<dis>connect' button is pressed
    };
}