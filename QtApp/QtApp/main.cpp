#include "QtApp.h"
#include <QtWidgets/QApplication>
#include <QtQml>

#include "MyRobot.h";



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtApp:: QtApp window;
    /*window.inputContext();

    QUrl source(QStringLiteral("qrc:/main.qml"));
    QQmlApplicationEngine engine;
    engine.load(source);*/


    window.show();
    
    return app.exec();
}
