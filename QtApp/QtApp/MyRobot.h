#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QMessageBox>

class MyRobot : public QObject {
    Q_OBJECT
public:
    MyRobot(QObject* parent);
    void MyTcpClient(QObject* parent = 0);
    void doConnect();
    void disConnect();
    void send(uint left_speed, uint right_speed, bool forward = true, bool control_speed = false);
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket* socket;
    QTimer* TimerEnvoi;
};

#endif // MYROBOT_H