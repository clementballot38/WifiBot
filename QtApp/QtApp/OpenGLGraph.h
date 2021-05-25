#pragma once


#include <QObject>
#include <QGLWidget>



class OpenGLGraph : QGLWidget
{
	Q_OBJECT


public:
	OpenGLGraph(QObject *parent = 0);
	void draw();


private:
	void initializeGL();
	void paintGL();
};

