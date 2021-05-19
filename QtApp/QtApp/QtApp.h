#pragma once

//#include <QtWidgets/QWidget>
#include <QMainWindow>
#include "ui_QtApp.h"


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
