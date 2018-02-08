#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QVector>

#include <QDebug>

class SerialMonitor
{
public:
    static void updateAvailablePorts(void);
    static QList<QString> getAvailablePortsNames(void);

    static bool connect(void);
    static void disconnect(void);

    static void setPort(QString portName);
    static void setBaudRate(qint32 baudrate);

    static void write(QString str);
    static void writeln(QString str);

    static QByteArray read(void);

private:
    SerialMonitor();
    static QList<QSerialPortInfo> availablePorts;
    static QSerialPort serial;
};

#endif // SERIALMONITOR_H
