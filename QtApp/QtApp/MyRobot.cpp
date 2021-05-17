#include "MyRobot.h"

MyRobot::MyRobot(QObject* parent) : QObject(parent) {
    /*
    // OG code
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    //      sender      signal             receiver     member
    connect(TimerEnvoi, SIGNAL(timeout()), this,        SLOT(MyTimerSlot())); //Send data to wifibot timer
    */

    this->doConnect();
    this->send(0, 0, true); // set speed to 0 L&R and forward
}



void MyRobot::MyTcpClient(QObject* parent) {

}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot with TCP
    // we need to wait...
    if (!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Timeout exceed for bot connection !");
        messageBox.setFixedSize(500, 200);
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::send(uint left_speed, uint right_speed, bool forward, bool control_speed)
{
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;   // always 255
    DataToSend[1] = 0x07;   // size in bytes (always 7 ?)

    // left motor control
    DataToSend[2] = left_speed;     // speed
    DataToSend[3] = 0x00;           // ?

    // right motor control
    DataToSend[4] = right_speed;    // speed
    DataToSend[5] = 0x00;           // ?

    // <left speed control on(1)/off(0)>  <left forward(1)/backward(0)>
    // <right speed control on(1)/off(0)> <right forward(1)/backward(0)>
    // <relay 4 on(1)/off(0)> <relay 3 on(1)/off(0)> <relay 2 on(1)/off(0)> <relay 1 (sensors) on(1)/off(0)>
    DataToSend[6] =  128 * control_speed + 64 * forward     // left motor
                    + 32 * control_speed + 16 * forward     // right motor
                    + 0;                                    // sensord

    // CRC (not used in TCP)
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;

    DataReceived.resize(21);

    // send data to wifibot timer
    //      sender      signal             receiver     member
    connect(TimerEnvoi, SIGNAL(timeout()), this,        SLOT(MyTimerSlot()));
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while (Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}
