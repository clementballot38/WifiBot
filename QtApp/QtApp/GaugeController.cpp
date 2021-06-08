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
