#ifndef RFID_H
#define RFID_H
#include <QObject>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSettings>




class RFID : public QObject
{
    Q_OBJECT

public:
    explicit RFID(QWidget *parent = 0);
    ~RFID();
signals:
    void dataready(QString data);

private slots:
    void dataread();
    void cleardata(QByteArray data);

private:

    QSerialPort *port;
    void initPort();


};

#endif // RFID_H
