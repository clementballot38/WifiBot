#include "GamepadController.h"


GamepadController::GamepadController(MyRobot* bot, QObject* parent)
	: robot(bot), QObject(parent), gamepad(0), gazForce(0), brakesForce(0) {
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
	if (gazForce - brakesForce >= 0)
		robot->turn(90.0f * val);
	else
		robot->turn(-90.0f * val);
}

void GamepadController::changeBrakes(double val) {
	this->brakesForce = val;
	this->updateSpeed();
}
void GamepadController::changeSpeed(double val) {
	this->gazForce = val;
	this->updateSpeed();
}
void GamepadController::updateSpeed() {
	int s = (int)(240 * (this->gazForce - this->brakesForce));
	qDebug() << s;
	robot->setSpeed(abs(s));
	robot->goForward(s >= 0);
}