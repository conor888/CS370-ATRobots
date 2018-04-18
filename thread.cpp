#include "thread.h"

void Worker::doWork(const QString &parameter) {
    QString result;
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}

Controller::Controller() {
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Controller::handleResults);
    workerThread.start();
}
Controller::~Controller() {
    workerThread.quit();
    workerThread.wait();
}
