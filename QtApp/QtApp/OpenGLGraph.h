#pragma once


#include <QObject>



class OpenGLGraph : QObject
{
	Q_OBJECT


public:
	OpenGLGraph(QObject *parent = 0);
	//void draw();


private:
	void initializeGL();
	void paintGL();
};

