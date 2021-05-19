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
    //void MyTcpClient(QObject* parent = 0);
    void doConnect();
    void disConnect();
    void createData(uint left_speed, uint right_speed, bool forward = true, bool control_speed = false);

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void keepAlive();
    //void MyTimerSlot();

private:
    QTcpSocket* socket;
    QTimer* TimerEnvoi;
    quint16 crc16(QByteArray buffer);

    void sendMessage();
    void receiveMessage();

    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
};

#endif // MYROBOT_H