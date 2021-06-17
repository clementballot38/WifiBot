#include "GaugeController.h"



int GaugeController::getValue() {
	return this->value;
}

// update the current value & notify all objects connected to the signal
void GaugeController::setValue(int val) {
	this->value = val;
	emit valueChanged(val);
}



int GaugeController::getMinValue() {
	return this->minValue;
}

// update the current min value & notify all objects connected to the signal
void GaugeController::setMinValue(int val) {
	this->minValue = val;
	emit minValueChanged(val);
}



int GaugeController::getMaxValue() {
	return this->maxValue;
}

// update the current max value & notify all objects connected to the signal
void GaugeController::setMaxValue(int val) {
	this->maxValue = val;
	emit maxValueChanged(val);
}
