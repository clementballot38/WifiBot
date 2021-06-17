#pragma once

#include <QObject>
#include <QGamepad>

#include "MyRobot.h"



/*
 * GamepadController class
 * -----------------------
 * 
 * This class can connect a gamepad to the bot to control it using the triggers and the joystick.
 * 
 * The controls are :
 *		Left trigger : brakes - reverse (when total speed is below 0)
 *		Right trigger : gaz
 *		Left joystick : direction
 * 
 * 
 * Tested with Xbox One and Xbox 360 controllers connected with USB.
 */



class GamepadController : QObject {
	Q_OBJECT

public:
	GamepadController(MyRobot* bot, QObject* parent = 0);		// constructor
	double getAcceleration() { return this->gazForce * 100; };	// returns the acceleration
	double getBrakes() { return this->brakesForce * 100; };		// returns the brakes force
	bool turnCameraLeft() { return this->cameraX < -0.5; };		// get if turn camera to the left
	bool turnCameraRight() { return this->cameraX > 0.5; };		// get if turn camera to the left
	bool turnCameraUp() { return this->cameraY < -0.5; };		// get if turn camera up
	bool turnCameraDown() { return this->cameraY > 0.5; };		// get if turn camera down

private:
	QGamepad* gamepad;					// the attached controller
	MyRobot* robot;						// the bot to control
	double gazForce, brakesForce;		// movement controls
	double cameraX = 0, cameraY = 0;	// camera controls
	void updateSpeed();					// send the updated speed & direction to the bot

private slots:
	void moveX(double val);			// handles the left joystick X axis changes
	void changeSpeed(double val);	// handles the right trigger changes
	void changeBrakes(double val);	// handles the left trigger changes
	void moveCameraX(double val);	// handles the right joystick X axis changes
	void moveCameraY(double val);	// handles the right joystick Y axis changes
};

