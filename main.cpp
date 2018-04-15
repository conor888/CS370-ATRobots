#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "atr2.h"
#include "atr2func.h"
#include "filelib.h"
#include <QApplication>
#include "arena.h"
#include "atr2var.h"
#include "window.h"
#include <QGridLayout>
#include "rgraph.h"
#include "cgraph.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("ATR2");

    std::string args[55];

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    atr2var av;

    arena *atr2a = new arena(&av);
    atr2a->setStyleSheet("background-color:black;");
    atr2a->setAttribute(Qt::WA_OpaquePaintEvent, true);
    //atr2a.show();

    QGridLayout *atr2l = new QGridLayout();

    rgraph **rgraphs = new rgraph*[6];

    cgraph *cycleg = new cgraph(&av);
    //one->setStyleSheet("background: rgb(255, 0, 0)");
    //one->update();

    window atr2w(&av, cycleg);
    atr2w.setLayout(atr2l);
    atr2w.setAttribute(Qt::WA_OpaquePaintEvent, true);

    atr2l->addWidget(atr2a, 0, 0);

    for (int i = 0; i < 6; i++) {
        rgraphs[i] = new rgraph(i, &av);
        atr2l->addWidget(rgraphs[i], i, 1);
    }

    atr2l->addWidget(cycleg, 7, 1);
    atr2l->setSpacing(5);
    atr2l->setContentsMargins(5, 5, 5, 5);
    atr2l->setRowMinimumHeight(6, 6);
    atr2l->setColumnMinimumWidth(0, 471);

    atr2w.setStyleSheet("background-color: rgb(168, 168, 168);");
    atr2w.show();

    WorkerThread *workerThread = new WorkerThread(&av, argc, args, atr2a, rgraphs, cycleg);
    //connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
    //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();

    return a.exec();
}
