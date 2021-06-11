#pragma once

#include <QObject>


class GaugeController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int value READ getValue NOTIFY valueChanged)
	Q_PROPERTY(int minValue READ getMinValue NOTIFY minValueChanged)
	Q_PROPERTY(int maxValue READ getMaxValue NOTIFY maxValueChanged)

public:
	GaugeController(QObject* parent) : QObject(parent), value(0) {};
	int getValue();
	void setValue(int val);

	int getMinValue();
	void setMinValue(int val);

	int getMaxValue();
	void setMaxValue(int val);

private:
	int value, minValue = 0, maxValue = 100;


signals:
	void valueChanged(int);
	void minValueChanged(int);
	void maxValueChanged(int);

};