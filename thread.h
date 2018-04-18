#ifndef THREAD_H
#define THREAD_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller();
    ~Controller();
public slots:
    void handleResults(const QString &);
signals:
    void operate(const QString &);
};

#endif // THREAD_H
