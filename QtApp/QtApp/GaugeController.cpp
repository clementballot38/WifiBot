#include "GaugeController.h"

int GaugeController::getValue()
{
	return this->value;
}

void GaugeController::setValue(int val)
{
	this->value = val;
	emit valueChanged(val);
}

int GaugeController::getMinValue()
{
	return this->minValue;
}

void GaugeController::setMinValue(int val)
{
	this->minValue = val;
	emit minValueChanged(val);
}

int GaugeController::getMaxValue()
{
	return this->maxValue;
}

void GaugeController::setMaxValue(int val)
{
	this->maxValue = val;
	emit maxValueChanged(val);
}
