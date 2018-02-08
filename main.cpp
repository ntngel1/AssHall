#include "asshallmain.h"
#include <QApplication>
#include <QList>
#include <QString>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<QString>>("QList<QString>");
    QApplication a(argc, argv);
    AssHallMain w;
    w.show();

    return a.exec();
}
