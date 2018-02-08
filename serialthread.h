#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialThread : public QObject
{
    Q_OBJECT
public:
    explicit SerialThread(QString s);

    static QList<QString> getAvailablePorts(void);

    QSerialPort serial;
private:
    QString name;
    bool isSerialConnected;
    QList<QString> availablePorts;

signals:
    void getData(QByteArray data);
    void connectionStateChanged(bool isConnected);
    void availablePortsChanged(QList<QString> ports);

public slots:
    void listen();

    void sendData(QString data);
};

#endif // SERIALTHREAD_H
