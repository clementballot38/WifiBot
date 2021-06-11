#pragma once

#include <QMediaPlayer>
#include <QtWidgets>
#include <QtWebEngineWidgets>
#include <QMessageBox>
#include <ui_QtApp.h>
#include <QTimer>

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
        UiController(Ui::QtAppClass* _ui, QString ip);  // constructor


    private:
        QTimer* gaugesTimer;        // timer used to update the gauges periodically
        Ui::QtAppClass* ui;         // attached UI
        MyRobot* bot;               // attached bot
        GamepadController* gamepad; // attached gamepad
        GaugeController *globalGauge, *speedGauge, *brakesGauge, *distGaugeLeft, *distGaugeRight, *distGaugeLeft2, *distGaugeRight2;    // attached gauges
        void keyPressEvent(QKeyEvent* ev);      // override the QObject keyPress event to handle keyboard controls
        void keyReleaseEvent(QKeyEvent* ev);    // override the QObject keyRelease event to handle keyboard controls
        void stopBot();     // stops the bot


    private slots:
        void upButton();        // called when the 'up' button is pressed
        void downButton();      // called when the 'down' button is pressed
        void leftButton();      // called when the 'left' button is pressed
        void rightButton();     // called when the 'right' button is pressed
        void updateGauges();    // called when the gauges are updated
    };
}