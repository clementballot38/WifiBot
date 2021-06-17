#include "GamepadController.h"


// constructor
GamepadController::GamepadController(MyRobot* bot, QObject* parent)
	: robot(bot), QObject(parent), gamepad(0), gazForce(0), brakesForce(0) {
	gamepad = new QGamepad(0, this);

	// connect the controls with the corresponding signal
	connect(gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(moveX(double)));
	connect(gamepad, SIGNAL(buttonL2Changed(double)), this, SLOT(changeBrakes(double)));// LT
	connect(gamepad, SIGNAL(buttonR2Changed(double)), this, SLOT(changeSpeed(double)));	// RT
	connect(gamepad, SIGNAL(axisRightXChanged(double)), this, SLOT(moveCameraX(double)));
	connect(gamepad, SIGNAL(axisRightYChanged(double)), this, SLOT(moveCameraY(double)));
}


// change direction based on left joystick orientation (left - right)
void GamepadController::moveX(double val) {
	if (gazForce - brakesForce >= 0)
		robot->turn(90.0f * val);
	else
		robot->turn(-90.0f * val);
}


// change the brakes force based on the left trigger value
void GamepadController::changeBrakes(double val) {
	this->brakesForce = val;
	this->updateSpeed();
}


// change the acceleration based on the right trigger value
void GamepadController::changeSpeed(double val) {
	this->gazForce = val;
	this->updateSpeed();
}


// update the bot speed & direction
void GamepadController::updateSpeed() {
	int s = (int)(240 * (this->gazForce - this->brakesForce));
	robot->setSpeed(abs(s));
	robot->goForward(s >= 0);
}


// update the camera X
void GamepadController::moveCameraX(double val) {
	this->cameraX = val;
}

// update the camera Y
void GamepadController::moveCameraY(double val) {
	this->cameraY = val;
}