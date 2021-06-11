#pragma once

#include <QObject>
#include <QGamepad>

#include "MyRobot.h"



class GamepadController : QObject {
	Q_OBJECT

public:
	GamepadController(MyRobot* bot, QObject* parent = 0);
	double getAcceleration() { return this->gazForce * 100; };
	double getBrakes() { return this->brakesForce * 100; };

private:
	QGamepad* gamepad;
	MyRobot* robot;
	double gazForce, brakesForce;
	void updateSpeed();

private slots:
	void moveX(double val);
	void changeSpeed(double val);
	void changeBrakes(double val);
};

