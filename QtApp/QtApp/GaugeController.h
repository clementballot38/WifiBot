#pragma once

#include <QObject>


class GaugeController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int value READ getValue NOTIFY valueChanged)

public:
	GaugeController(QObject* parent) : QObject(parent), value(0) {};
	int getValue();
	void setValue(int val);

private:
	int value;


signals:
	void valueChanged(int);

};