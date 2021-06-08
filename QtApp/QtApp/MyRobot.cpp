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
}

void MyRobot::keepAlive() {
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
    //this->battery = (((unsigned int)((unsigned char)recv[2])) * 100.0 / 255.0);
   /* this->cpt_ir1 = (int)recv[3];
    this->cpt_ir2 = (int)recv[4];*/
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting"; // this is not blocking call
    socket->connectToHost("192.168.1.11", 15020); // connection to wifibot with TCP
    if (!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Timeout exceed for bot connection !");
        messageBox.setFixedSize(500, 200);
        return;
    }

    qDebug("Connected, starting");
    TimerEnvoi->start();
}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::createData(uint left_speed, uint right_speed, bool forward, bool control_speed)
{
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

    // char 7
    if(forward)
        DataToSend.append((char)0b01011111);
    else
        DataToSend.append((char)0b00001111);

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
    qDebug() << "Read : " << DataReceived;
    this->distLeft = (int)DataReceived[3];
    this->distRight = (int)DataReceived[4];

}



void MyRobot::setSpeed(int val) {
    this->speed = val;
    int left_speed, right_speed;
    if (this->forward) {
        left_speed = this->dirAngle < 0 ? (int)((float)(this->speed) * cos(this->dirAngle * PI / 180.0f)) : this->speed;
        right_speed = this->dirAngle > 0 ? (int)((float)(this->speed) * cos(this->dirAngle * PI / 180.0f)) : this->speed;
    }
    else {
        left_speed = this->dirAngle > 0 ? (int)((float)(this->speed) * cos(this->dirAngle * PI / 180.0f)) : this->speed;
        right_speed = this->dirAngle < 0 ? (int)((float)(this->speed) * cos(this->dirAngle * PI / 180.0f)) : this->speed;
    }
    this->createData(left_speed, right_speed, this->forward);
}

// -90 : full left, 0 : straight, +90 : full right
void MyRobot::turn(float angle) {
    if (angle >= -90 && angle <= 90)
        this->dirAngle = angle;
    this->setSpeed(this->speed);
}

void MyRobot::goForward(bool f) {
    this->forward = f;
}