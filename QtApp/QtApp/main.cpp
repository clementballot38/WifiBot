#include "QtApp.h"
#include <QtWidgets/QApplication>

#include "MyRobot.h";



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtApp window;
    window.show();

    MyRobot robot(NULL);
    //robot.connected();
    robot.send(10, 100);
    
    return app.exec();
}
