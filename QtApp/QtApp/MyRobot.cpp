#include "MyRobot.h"


// constructor
MyRobot::MyRobot(QObject* parent, QString _ip)
    : QObject(parent), ip(_ip), battery(0), socket(0) {

    // initialize the datas sent to the bot
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

    // timer to automatically send the updated datas to the bot and keep the connection alive
    TimerEnvoi = new QTimer();
    TimerEnvoi->setInterval(100);
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(keepAlive()));
}

// periodically send datas to the bot to keep the connection alive
void MyRobot::keepAlive() {
    sendMessage();
    receiveMessage();
}

// send datas to the bot
void MyRobot::sendMessage() {
    socket->write(DataToSend);
    socket->flush();
}

// fetch datas from the bot
void MyRobot::receiveMessage() {
    DataReceived = socket->readAll();
}

// connect to the bot
void MyRobot::doConnect() {
    // create a socket to send & receive datas and connect its events to signals to handle them
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting";
    socket->connectToHost(this->ip, 15020); // connecto to the bot with TCP
    if (!socket->waitForConnected(5000)) {
        // bot not found, show error message
        qDebug() << "Error: " << socket->errorString();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Timeout exceed for bot connection !");
        messageBox.setFixedSize(500, 200);
        return;
    }

    // bot connected successfully so start the timer
    qDebug("Connected, starting");
    TimerEnvoi->start();
}

// disconnect from the bot
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

// create the data packet with the given speeds & direction
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

// calculate the CRC16 of the given packet
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

// event called when the bot is connected
void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
    this->connection_status = true;
}

// event called when the bot is disconnected
void MyRobot::disconnected() {
    qDebug() << "disconnected...";
    this->connection_status = false;
}

// event called when datas are sent to the bot
void MyRobot::bytesWritten(qint64 bytes) {
    //qDebug() << bytes << " bytes written : " << DataToSend;
}

// event called when datas are received
void MyRobot::readyRead() {
    DataReceived = socket->readAll();
    this->distLeft = (int)DataReceived[3];
    this->distLeft2 = (int)DataReceived[4];
    this->distRight = (int)DataReceived[11];
    this->distRight2 = (int)DataReceived[12];
}

// update the bot's speed
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

// update the bot's direction
void MyRobot::turn(float angle) {
    // -90 : full left, 0 : straight, +90 : full right
    if (angle >= -90 && angle <= 90)
        this->dirAngle = angle;
    this->setSpeed(this->speed);
}

// update the bot's direction
void MyRobot::goForward(bool f) {
    this->forward = f;
}

// get the bot's battery level
unsigned int MyRobot::getBattery() {
    unsigned int battery = (unsigned char)DataReceived[2] * 100.0 / 255.0;
    return battery;
}
