#include "rfid.h"

#include <QDebug>

RFID::RFID(QWidget *parent) : QObject(parent)
{
    port = new QSerialPort();
    connect(port, SIGNAL(readyRead()), this, SLOT(dataread()));
    initPort();
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->open(QIODevice::ReadOnly);
}

void RFID::initPort(){
    QSettings settings("/RFID.ini", QSettings::IniFormat);
    qDebug()<<settings.value("config/port","rien").toString();
    port->setPortName(settings.value("config/port","ttyUSB0").toString());
}

void RFID::dataread(){
    QString nombre1,nombre2,nombre3;
    QByteArray data= port->readAll();
    qDebug()<<"Data : "<<data;
    nombre1=data[30];
    nombre2=data[31];
    nombre3=nombre1+nombre2;
    qDebug()<<"nombre1 : "<<nombre1;
    qDebug()<<"nombre2 : "<<nombre2;
    qDebug()<<"nombre3 : "<<nombre3;
    // qDebug()<<"*--------------------------------------------------------------------";
    emit dataready(nombre3);
    emit cleardata(data);
}

void RFID::cleardata(QByteArray data){
    qDebug()<<"trame1 : "<<data;
    qDebug()<<"trame2 : "<<data;
}

RFID::~RFID()
{

}
