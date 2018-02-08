#include "serialmonitor.h"

QList<QSerialPortInfo> SerialMonitor::availablePorts;
QSerialPort SerialMonitor::serial;

SerialMonitor::SerialMonitor()
{
}

void SerialMonitor::updateAvailablePorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();

            // Example use QSerialPort
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
                serial.close();
    }

    availablePorts = QSerialPortInfo::availablePorts();
}

QList<QString> SerialMonitor::getAvailablePortsNames()
{
    QList<QString> portsNames;
    portsNames.reserve(availablePorts.size());

    foreach (const QSerialPortInfo &info, availablePorts) {
        portsNames.push_back(info.portName());
    }

    return portsNames;
}

bool SerialMonitor::connect()
{
    return serial.open(QIODevice::ReadWrite);
}

void SerialMonitor::setPort(QString portName)
{
    serial.setPortName(portName);
}

void SerialMonitor::setBaudRate(qint32 baudrate)
{
    serial.setBaudRate(baudrate);
}

void SerialMonitor::write(QString str)
{
    if (serial.isOpen())
        serial.write(str.toUtf8());
}
