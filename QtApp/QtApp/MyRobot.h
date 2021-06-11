#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>
#include <QMessageBox>
#include <math.h>



/*
 * MyRobot class
 * -----------------------
 *
 * This class connects to a wifibot, controls it, fetches datas from it and manages the connection to it.
 * Original code : https://github.com/dginhac/wifibot/tree/master/qt
 */



class MyRobot : public QObject {
    Q_OBJECT


public:
    MyRobot(QObject* parent, QString _ip);  // constructor
    void doConnect();   // connect to the bot
    void disConnect();  // disconnect from the bot

    void setSpeed(int val);         // update the bot's speed
    void turn(float angle);         // update the bot's angle
    void goForward(bool f = true);  // update the bot's direction

    int getSpeed() { return this->forward ? this->speed : -this->speed; };  // get the current bot's speed
    int getDistLeft() { return this->distLeft; };       // get the left IR sensor value
    int getDistRight() { return this->distRight; };     // get the right IR sensor value
    int getDistLeft2() { return this->distLeft2; };     // get the second left IR sensor value
    int getDistRight2() { return this->distRight2; };   // get the second right IR sensor value

/*signals:
    void updateUI(const QByteArray Data);*/


public slots:
    void connected();       // called when the connection is established
    void disconnected();    // called when the connection is closed

    void bytesWritten(qint64 bytes);    // called when datas are sent to the bot
    void readyRead();   // called when datas are received
    void keepAlive();   // called by a timer to keep the connection alive


private:
    QTcpSocket* socket;                 // connection socket
    QTimer* TimerEnvoi;                 // timer to keep the connection alive
    quint16 crc16(QByteArray buffer);   // calculate data's CRC16

    QString ip;     // bot's IP adress

    void createData(uint left_speed, uint right_speed, bool forward = true, bool control_speed = false);    // create datas from given parameters
    void sendMessage();     // send datas to the bot
    void receiveMessage();  // receive datas from the bot

    float dirAngle = 0.0f;          // current angle
    const float PI = 3.14159265f;   // pi
    int speed = 0;                  // current speed
    bool forward = true;            // current direction
    int distLeft = 127, distRight = 127, distLeft2 = 127, distRight2 = 127; // current IR sensors values

    QByteArray DataToSend;      // current datas to send to the bot
    QByteArray DataReceived;    // current datas received from the bot
};

#endif // MYROBOT_H