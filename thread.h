#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include "arena.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(atr2var* avtemp, int argctemp, std::string argvtemp[], arena* parent, rgraph** rgraphstemp, cgraph* cyclegtemp, window* atr2wtemp);
    Worker(atr2var* avtemp, int argctemp, std::string argvtemp[]);

private:
    int argc;
    atr2var *av;
    arena *atr2a;
    std::string *argv;
    rgraph **rgraphs;
    cgraph *cycleg;
    window *atr2w;

    bool graphix;

public slots:
    void doWork();

signals:
    void resultReady(const QString &result);
};





class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller(atr2var* avtemp, int argctemp, std::string argvtemp[], arena* parent, rgraph** rgraphstemp, cgraph* cyclegtemp, window* atr2wtemp);
    Controller(atr2var* avtemp, int argctemp, std::string argvtemp[]);
    ~Controller();

private:
    int argc;
    atr2var *av;
    arena *atr2a;
    std::string *argv;
    rgraph **rgraphs;
    cgraph *cycleg;
    window *atr2w;

public slots:
    //void handleResults(const QString &);
signals:
    void operate();
};

#endif // THREAD_H
