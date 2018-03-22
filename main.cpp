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

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    std::string args[argc];

    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    atr2var av;

    arena atr2a(&av);
    atr2a.show();

    WorkerThread *workerThread = new WorkerThread(&av, argc, args, &atr2a);
    workerThread->start();

    return a.exec();
}
