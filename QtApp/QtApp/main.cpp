#include "QtApp.h"
#include <QtWidgets/QApplication>

#include "MyRobot.h";



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtApp window;
    window.show();

    MyRobot robot(NULL);
    return app.exec();
}
