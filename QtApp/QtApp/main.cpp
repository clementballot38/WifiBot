#include <QtQml>

#include "UiController.h"
#include "MyRobot.h";
#include "ui_QtApp.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget* widget = new QWidget;
    Ui::QtAppClass ui;
    ui.setupUi(widget);

    UiController::UiController controller(&ui);
    

    widget->show();

    return app.exec();
}
