#include "serialthread.h"

SerialThread::SerialThread(QString s) : name(s)
{

}

void SerialThread::listen()
{
    while (1) {
        if (serial.isOpen() && serial.bytesAvailable() > 0)
            emit getData(serial.readAll());

        if (serial.isOpen() != isSerialConnected) {
            isSerialConnected = serial.isOpen();
            emit connectionStateChanged(isSerialConnected);
        }

        QList<QString> ports = getAvailablePorts();
        if (ports != availablePorts) {
            availablePorts = ports;
            emit availablePortsChanged(availablePorts);
            if(!availablePorts.contains(serial.portName())) {
                emit connectionStateChanged(false);
                isSerialConnected = false;
                serial.close();
            }
        }

        QThread::msleep(150);
    }
}

void SerialThread::sendData(QString data)
{
    qint64 err = serial.write(data.toUtf8());
    if (err == -1) {
        serial.close();
        isSerialConnected = false;
        emit connectionStateChanged(false);
    }
}

QList<QString> SerialThread::getAvailablePorts()
{
    QList<QString> portsNames;
    portsNames.reserve(QSerialPortInfo::availablePorts().size());

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        portsNames.push_back(info.portName());
    }

    return portsNames;
}
