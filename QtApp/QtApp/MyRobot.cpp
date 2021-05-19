#include "MyRobot.h"

MyRobot::MyRobot(QObject* parent) : QObject(parent) {
    
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
    TimerEnvoi->setInterval(100);
    connect(TimerEnvoi, SIGNAL(timeout()), this,        SLOT(keepAlive()));

    this->doConnect();

    /*this->doConnect();
    this->send(0, 0, true); // set speed to 0 L&R and forward*/
}



/*void MyRobot::MyTcpClient(QObject* parent) {

}*/


void MyRobot::keepAlive() {
    //createData(200, 0);
    sendMessage();
    receiveMessage();
}


void MyRobot::sendMessage() {
    socket->write(DataToSend);
    socket->flush();
}

void MyRobot::receiveMessage() {
    DataReceived = socket->readAll();
    qDebug(DataReceived);
    /*this->battery = (((unsigned int)((unsigned char)recv[2])) * 100.0 / 255.0);
    this->cpt_ir1 = (int)recv[3];
    this->cpt_ir2 = (int)recv[4];*/
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.11", 15020); // connection to wifibot with TCP
    // we need to wait...
    if (!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Timeout exceed for bot connection !");
        messageBox.setFixedSize(500, 200);
        return;
    }
    else {
        qDebug("start");
        TimerEnvoi->start();
    }
}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::createData(uint left_speed, uint right_speed, bool forward, bool control_speed)
{
    /*DataToSend.resize(9);
    DataToSend[0] = 0xFF;   // always 255
    DataToSend[1] = 0x07;   // size in bytes (always 7 ?)

    // left motor control
    DataToSend[2] = left_speed;     // speed
    DataToSend[3] = 0x00;           // forward/backward

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
    while (Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
    qDebug("send");*/



    DataToSend.clear();

    // frame infos
    DataToSend.append((char)0xff);
    DataToSend.append((char)0x07);

    // left
    DataToSend.append((char)left_speed);
    DataToSend.append((char)0x00);

    // right
    DataToSend.append((char)right_speed);
    DataToSend.append((char)0x00);

    if(forward)
        DataToSend.append((char)0b01010000);
    else
        DataToSend.append((char)0b00000000);

    quint16 crc = crc16(DataToSend);
    DataToSend.append((char)crc);
    DataToSend.append((char)(crc >> 8));
}


quint16 MyRobot::crc16(QByteArray byteArray) {
    unsigned char* data = (unsigned char*)byteArray.constData();
    quint16 crc = 0xFFFF;
    quint16 Polynome = 0xA001;
    quint16 Parity = 0;
    for (int pos = 1; pos < byteArray.length(); pos++) {
        crc ^= *(data + pos);
        for (unsigned int CptBit = 0; CptBit <= 7; CptBit++) {
            Parity = crc;
            crc >>= 1;
            if (Parity % 2 == true) crc ^= Polynome;
        }
    }
    return crc;
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written : " << DataToSend;
}

void MyRobot::readyRead() {
    DataReceived = socket->readAll();
    // emit updateUI(DataReceived);
    qDebug() << "Read : " << DataReceived;
}

/*void MyRobot::MyTimerSlot() {
    //qDebug() << "Timer...";

    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0xf0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;



    while (Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}
*/