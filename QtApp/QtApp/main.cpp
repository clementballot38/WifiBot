#include <QtQml>

#include "UiController.h"
#include "MyRobot.h";
#include "ui_QtApp.h"



/* 
 * WifiBot GUI
 * -----------
 * 
 * Created by Clément BALLOT & Jules GELUS
 * 
 * 
 * 
 * This program is a GUI developped in C++ with Qt to control the WifiBot (see https://github.com/dginhac/wifibot) for documentation).
 * 
 * This is the app's entry point.
 */



int main(int argc, char *argv[])
{
    // app context
    QApplication app(argc, argv);

    // create the UI from QtApp.ui
    Ui::QtAppClass ui;

    // main view
    QWidget* widget = new QWidget;
    ui.setupUi(widget);

    // bind the UI controller to the UI
    UiController::UiController controller(&ui, "192.168.1.11");
    
    // display the main window
    widget->show();

    // execute the app
    return app.exec();
}
