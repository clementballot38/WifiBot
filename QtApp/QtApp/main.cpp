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



UiController::UiController* controller; // main controller


// called when an key is pressed
void QWidget::keyPressEvent(QKeyEvent* ev) {
    controller->keyPressEvent(ev);
}

// called when a key is released
void QWidget::keyReleaseEvent(QKeyEvent* ev) {
    controller->keyReleaseEvent(ev);
}



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
    controller = new UiController::UiController(&ui, "192.168.1.106");
    
    // display the main window
    widget->show();

    // execute the app
    return app.exec();
}
