#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QProcess *atr2 = new QProcess();
    atr2->setProcessChannelMode(QProcess::ForwardedChannels);

    MainWindow w(atr2);

    QObject::connect(atr2, SIGNAL(started()), &w, SLOT(hide()));
    QObject::connect(atr2, SIGNAL(finished(int, QProcess::ExitStatus)), &w, SLOT(show()));
    QObject::connect(atr2, SIGNAL(finished(int, QProcess::ExitStatus)), &w, SLOT(raise()));

    w.show();

    return a.exec();
}
