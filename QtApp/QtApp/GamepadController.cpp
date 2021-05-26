#include "GamepadController.h"


GamepadController::GamepadController(MyRobot* bot, QObject* parent)
	: robot(bot), QObject(parent), gamepad(0), goForward(true) {
	/*auto gamepads = QGamepadManager::instance()->connectedGamepads();
	qDebug() << gamepads;
	if (gamepads.isEmpty()) {
		qDebug() << "No gamepad detected";
		return;
	}
	qDebug() << "Using first detected controller";*/


	//gamepad = new QGamepad(*gamepads.begin(), this);
	gamepad = new QGamepad(0, this);

	connect(gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(moveX(double)));
	connect(gamepad, SIGNAL(buttonL2Changed(double)), this, SLOT(changeBrakes(double)));// LT
	connect(gamepad, SIGNAL(buttonR2Changed(double)), this, SLOT(changeSpeed(double)));	// RT
}


void GamepadController::moveX(double val) {
	qDebug() << "X:" << val;
	if (this->goForward)
		robot->turn(90.0f * val);
	else
		robot->turn(-90.0f * val);
}

void GamepadController::changeBrakes(double val) {
	qDebug() << "Brakes:" << val;
	robot->setSpeed(val * 240);
	this->goForward = false;
	robot->goForward(false);
}
void GamepadController::changeSpeed(double val) {
	qDebug() << "Trigger:" << val;
	robot->setSpeed(val * 240);
	this->goForward = true;
	robot->goForward();
}