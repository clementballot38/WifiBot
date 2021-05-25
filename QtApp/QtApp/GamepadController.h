#pragma once

#include <QObject>
#include <QGamepad>

#include "MyRobot.h"



class GamepadController : QObject {
	Q_OBJECT

public:
	GamepadController(MyRobot* bot, QObject* parent = 0);

private:
	QGamepad* gamepad;
	MyRobot* robot;

private slots:
	void moveX(double val);
	void changeSpeed(double val);
	//void changeBrakes(double val);
};

