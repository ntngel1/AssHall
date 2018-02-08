#include "asshallmain.h"
#include "ui_asshallmain.h"

AssHallMain::AssHallMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssHallMain)
{
    ui->setupUi(this);

    thread = new QThread;
    serialmonitor = new SerialThread("serialmonitor");
    serialmonitor->moveToThread(thread);

    connect(serialmonitor, SIGNAL(getData(QByteArray)), this, SLOT(readSerial(QByteArray)));
    connect(serialmonitor, SIGNAL(connectionStateChanged(bool)), this, SLOT(connectionState_changed(bool)));
    connect(serialmonitor, SIGNAL(availablePortsChanged(QList<QString>)), this, SLOT(updateAvailableDevices(QList<QString>)));
    connect(thread, SIGNAL(started()), serialmonitor, SLOT(listen()));

    thread->start();
}

AssHallMain::~AssHallMain()
{
    delete ui;
}

void AssHallMain::updateAvailableDevices(QList<QString> ports)
{
    ui->portComboBox->clear();
    foreach (const QString& name, ports) {
        ui->portComboBox->addItem(name);
    }
}

void AssHallMain::on_baudrateComboBox_activated(const QString &arg1)
{
    qint32 baudrate = arg1.toInt();
    if (baudrate == 0) {
        ui->baudrateComboBox->setCurrentIndex(0);
    }
}

void AssHallMain::on_sendButton_clicked(void)
{
    QString data = ui->sendDataEdit->text();

    if (data.isEmpty())
        return;

    ui->sendDataEdit->clear();

    serialmonitor->sendData(data);
    ui->dataEdit->setTextColor(QColor(0,0,255));
    ui->dataEdit->append("> " + data);
}

void AssHallMain::on_connectButton_clicked(void)
{
    if (serialmonitor->serial.isOpen())
        serialmonitor->serial.close();
    else {
        serialmonitor->serial.setPortName(ui->portComboBox->currentText());
        serialmonitor->serial.setBaudRate(ui->baudrateComboBox->currentText().toInt());
        serialmonitor->serial.open(QIODevice::ReadWrite);
    }
}

void AssHallMain::readSerial(QByteArray data)
{
    if (data.isEmpty())
        return;

    ui->dataEdit->moveCursor(QTextCursor::End);
    ui->dataEdit->setTextColor(QColor(0,0,0));
    ui->dataEdit->append(data);
}

void AssHallMain::on_sendDataEdit_returnPressed()
{
    on_sendButton_clicked();
}

void AssHallMain::on_aboutProgramAction_triggered()
{
    AboutProgramDialog* d = new AboutProgramDialog(this);
    d->setModal(false);
    d->show();
}

void AssHallMain::on_clearButton_clicked()
{
    ui->dataEdit->clear();
}

void AssHallMain::connectionState_changed(bool isConnected)
{
    if (isConnected)
        ui->connectButton->setText("Отсоединиться");
    else {
        ui->connectButton->setText("Соединиться");
    }
}
