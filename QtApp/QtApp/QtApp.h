#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtApp.h"

class QtApp : public QWidget
{
    Q_OBJECT

public:
    QtApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtAppClass ui;
};
