#ifndef ASSHALLMAIN_H
#define ASSHALLMAIN_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QList>

#include "serialthread.h"
#include "aboutprogramdialog.h"

namespace Ui {
class AssHallMain;
}

class AssHallMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssHallMain(QWidget *parent = 0);
    ~AssHallMain();

private slots:
    void on_baudrateComboBox_activated(const QString &arg1);

    void on_sendButton_clicked();

    void on_connectButton_clicked();

    void readSerial(QByteArray data);

    void on_sendDataEdit_returnPressed();

    void on_aboutProgramAction_triggered();

    void on_clearButton_clicked();

    void connectionState_changed(bool isConnected);

    void updateAvailableDevices(QList<QString> ports);

private:
    Ui::AssHallMain *ui;

    SerialThread* serialmonitor;
    QThread* thread;
};

#endif // ASSHALLMAIN_H
