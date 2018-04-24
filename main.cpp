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
#include "thread.h"

int main(int argc, char *argv[]) {
    bool graphix = true;

    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("ATR2");

    std::string args[100];

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
        if (args[i] == "-G") {
            graphix = false;
        }
    }

    atr2var av;
    Controller *atr2c;

    QGridLayout *atr2l;
    rgraph **rgraphs;
    cgraph *cycleg;
    window *atr2w;

    if (graphix) {
        arena *atr2a = new arena(&av);
        atr2a->setStyleSheet("background-color:black;");
        atr2a->setAttribute(Qt::WA_OpaquePaintEvent, true);
        //atr2a.show();

        atr2l = new QGridLayout();

        rgraphs = new rgraph*[6];

        cycleg = new cgraph(&av);

        atr2w = new window(&av, cycleg, rgraphs);
        atr2w->setLayout(atr2l);
        atr2w->setAttribute(Qt::WA_OpaquePaintEvent, true);

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

        atr2w->setStyleSheet("background-color: rgb(168, 168, 168);");
        atr2w->show();

        atr2c = new Controller(&av, argc, args, atr2a, rgraphs, cycleg, atr2w);
    } else {
        //No graphics
        atr2c = new Controller(&av, argc, args);
    }

    atr2c->operate();

    return a.exec();
}
