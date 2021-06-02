#pragma once

//#include <QtWidgets/QWidget>
#include <QMainWindow>
#include "ui_QtApp.h"
#include <QMediaPlayer>
#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "MyRobot.h";

#include <QMessageBox>

class QtApp : public QMainWindow
{
    Q_OBJECT

public:
    QtApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtAppClass ui;
    MyRobot *bot;

private slots:
    void upButton();
    void downButton();
    void leftButton();
    void rightButton();
    void stopButton();
};
    private:
        Ui::QtAppClass ui;
        MyRobot* bot;
        GamepadController* gamepad;
        void updateMovement(int speed, Direction dir, bool forward);
        int speed;
        QWebEngineView* streamView;
        QNetworkAccessManager* manager;
