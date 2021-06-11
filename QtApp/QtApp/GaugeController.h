#pragma once

#include <QObject>



/*
 * GaugeController class
 * -----------------------
 *
 * This class can update a custom gauge widget.
 *
 * 
 * 
 * Widget setup :
 * 
 *	To use this class with a custom widget, it needs to implement at least a value property.
 *	To do so, if the widget you want to control does not implements a value property, add this
 * line to its .qml file :
 *		property int value: controller.value
 * 
 * 
 * 
 * C++ setup :
 * 
 *	To set the widget's value from the .cpp :
 *		1- Create a GaugeController object
 *      2- Add this line to you *.cpp :
 *			<Ui::QtAppClass*>
 *				-><widget name in .ui file>
 *				->rootContext()
 *				->setContextProperty("controller", <GaugeController);
 *		3- Update the widget's value with the following line :
 *				<GaugeController>->setValue(<value>);
 *		4- (optionnal) If yout widget has a min/max value, you can update them with the
			following code :
 *				<GaugeController>->setMinValue(<value>);
 *				<GaugeController>->setMaxValue(<value);
 */


class GaugeController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int value READ getValue NOTIFY valueChanged)				// bind the value property
	Q_PROPERTY(int minValue READ getMinValue NOTIFY minValueChanged)	// bind the minValue property
	Q_PROPERTY(int maxValue READ getMaxValue NOTIFY maxValueChanged)	// bind the maxValue propertn

public:
	GaugeController(QObject* parent) : QObject(parent), value(0) {};	// constructor
	int getValue();			// get the current value
	void setValue(int val);	// set the current value

	int getMinValue();			// get the current min value
	void setMinValue(int val);	// set the current min value

	int getMaxValue();			// get the current max value
	void setMaxValue(int val);	// set the current max value

private:
	int value, minValue = 0, maxValue = 100;	// internal values


signals:
	void valueChanged(int);		// handles the value changes
	void minValueChanged(int);	// handles the min value changes
	void maxValueChanged(int);	// handles the max value changes

};