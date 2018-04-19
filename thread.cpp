#include "thread.h"

Worker::Worker(atr2var* avtemp, int argctemp, std::string argvtemp[], arena* parent, rgraph** rgraphstemp, cgraph* cyclegtemp) {
    av = avtemp;
    argc = argctemp;
    argv = argvtemp;
    atr2a = parent;
    rgraphs = rgraphstemp;
    cycleg = cyclegtemp;

    //loop = new QEventLoop();

    //QObject::connect(parent, SIGNAL(donePainting()), loop, SLOT(quit()));
}

void Worker::doWork() {
    QString result;

    //atr2 atr2(av, atr2a, loop);
    atr2 atr2(av, atr2a, rgraphs, cycleg);

    atr2.init(argc, argv);

    int i, j, k, l, n, w;

    if(av->graphix) {
        atr2.begin_window();
    }
    if(av->matches > 0) {
        for (i = 0; i < av->matches; i++) {
            atr2.bout();
        }
    }
    if(!av->graphix) {
        std::cout << std::endl;
    }
    if(av->quit) {
        exit(0);
    }
    if(av->matches > 1) {
        std::cout << std::endl << std::endl;
        //graph_mode(false);
        //textcolor(15);
        std::cout << "Bout complete! (" << av->matches << " av.matches)" << std::endl;
        k = 0;
        w = 0;
        for (i = 0; i < av->num_robots; i++) {
            if (av->robot[i].wins == w) {
                k++;
            }
            if (av->robot[i].wins > w) {
                k = 1;
                n = i;
                w = av->robot[i].wins;
            }
        }
        std::cout << "Robot           Wins  Matches  Kills  Deaths    Shots" << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        for (i = 0; i < av->num_robots; i++) {
            //textcolor(robot_color(i));
            std::cout << atr2func::addfront(atr2func::cstr(i+1), 2) << " - " << atr2func::addrear(av->robot[i].fn, 8)
                      << atr2func::addfront(atr2func::cstr(av->robot[i].wins), 7) << atr2func::addfront(atr2func::cstr(av->robot[i].trials), 8)
                      << atr2func::addfront(atr2func::cstr(av->robot[i].kills), 8) << atr2func::addfront(atr2func::cstr(av->robot[i].deaths), 8)
                      << atr2func::addfront(atr2func::cstr(av->robot[i].shots_fired), 9) << std::endl;
        }
        //textcolor(15);
        std::cout << std::endl;
        if (k == 1) {
            std::cout << "Robot #" << n + 1 << " (" << av->robot[n].fn << ") wins the bout! (score: " << w << "/" << av->matches << ")" << std::endl;
        } else {
            std::cout << "There is no clear victor!" << std::endl;
        }
        std::cout << std::endl;
    } else if (av->graphix) {
        //graph_mode(false);
        //show_statistics();
    }
    if (av->report) {
        atr2.write_report();
    }

    atr2.shutdown();

    emit resultReady(result);
}

Controller::Controller(atr2var* avtemp, int argctemp, std::string argvtemp[], arena* parent, rgraph** rgraphstemp, cgraph* cyclegtemp) {
    av = avtemp;
    argc = argctemp;
    argv = argvtemp;
    atr2a = parent;
    rgraphs = rgraphstemp;
    cycleg = cyclegtemp;

    Worker *worker = new Worker(av, argc, argv, atr2a, rgraphs, cycleg);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    //connect(worker, &Worker::resultReady, this, &Controller::handleResults);
    workerThread.start();
}
Controller::~Controller() {
    workerThread.quit();
    workerThread.wait();
}
