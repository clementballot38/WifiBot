#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QMessageBox>

#include <math.h>

class MyRobot : public QObject {
    Q_OBJECT


public:
    MyRobot(QObject* parent);
    //void MyTcpClient(QObject* parent = 0);
    void doConnect();
    void disConnect();

    void setSpeed(int val);
    void turn(float angle);
    void goForward(bool f = true);
    unsigned int getBattery();

signals:
    void updateUI(const QByteArray Data);


public slots:
    void connected();
    void disconnected();

    void bytesWritten(qint64 bytes);
    void readyRead();
    void keepAlive();


private:
    QTcpSocket* socket;
    QTimer* TimerEnvoi;
    quint16 crc16(QByteArray buffer);

    void createData(uint left_speed, uint right_speed, bool forward = true, bool control_speed = false);
    void sendMessage();
    void receiveMessage();

    float dirAngle = 0.0f;
    const float PI = 3.14159265f;
    int speed = 0;
    bool forward = true;
    int battery;
    
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
};

#endif // MYROBOT_H