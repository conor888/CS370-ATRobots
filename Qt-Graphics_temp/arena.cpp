//
// Created by conor on 3/20/2018.
//

#include <QtWidgets>
#include "arena.h"
#include "atr2.h"
#include "atr2func.h"

arena::arena(atr2var* avtemp, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("ATR2"));
    //resize(470, 470);
    resize(940, 940);

    av = avtemp;

    //p = new QPainter(this);
    //p->setBackgroundMode(Qt::NoBackground);

    //WorkerThread *workerThread = new WorkerThread(&av, argc, argv, this);
    //connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
    //connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    //workerThread->start();
}

void arena::update_vars(int nn) {
    //ag = av;
    n = nn;
}

void arena::clear_arena() {
    QPainter p(this);

    p.save();
    p.restore();
}

void arena::paintEvent(QPaintEvent *)
{
    int side = qMin(width(), height());
    //QPainter p(this);
    //p->setRenderHint(QPainter::Antialiasing);
    //p->translate(width() / 2, height() / 2);
    //p->scale(side / 200.0, side / 200.0);

    QPainter p(this);

    //p->begin(this);

    p.setBrush(Qt::NoBrush);

    p.save();

    p.setPen(QPen(Qt::black, 18));
    //erase
    /*if (n == 0) {
        p.fillRect(0, 0, 940, 940, Qt::black);
    }*/
    if (av->robot[n].lshields) {
        p.drawEllipse(av->robot[n].ltx[4], av->robot[n].lty[4], atr2var::robot_scale, atr2var::robot_scale);
    }
    if (av->robot[n].arc_count < 0) {
        p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[6], av->robot[n].lty[6]);
        p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[7], av->robot[n].lty[7]);
        if (av->robot[n].scanrange < 1500) {
            p.drawArc(av->robot[n].ltx[4], av->robot[n].lty[4], (int)round(av->robot[n].scanrange * atr2var::screen_scale), (int)round(av->robot[n].scanrange * atr2var::screen_scale), av->robot[n].lstartarc, av->robot[n].lendarc);
        }
    }
    if (av->robot[n].sonar_count > 0) {
        p.drawEllipse(av->robot[n].ltx[4], av->robot[n].lty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
    }
    if (av->robot[n].armor > 0) { //only erase body if still alive, that way we leave a "corpse" when dead
        p.drawLine(av->robot[n].ltx[1], av->robot[n].lty[1], av->robot[n].ltx[2], av->robot[n].lty[2]);
        p.drawLine(av->robot[n].ltx[2], av->robot[n].lty[2], av->robot[n].ltx[3], av->robot[n].lty[3]);
        p.drawLine(av->robot[n].ltx[3], av->robot[n].lty[3], av->robot[n].ltx[1], av->robot[n].lty[1]);
        p.drawLine(av->robot[n].ltx[4], av->robot[n].lty[4], av->robot[n].ltx[5], av->robot[n].lty[5]);
    }

    p.setPen(QPen(atr2func::robot_color(n), 2));

    if (av->robot[n].armor > 0) {
        //setcolor(robot_color(n) & 7);
        if (av->robot[n].shields_up) {
            p.drawEllipse(av->robot[n].tx[4], av->robot[n].ty[4], atr2var::robot_scale, atr2var::robot_scale);
        }
        //setcolor(robot_color(n));
        p.drawLine(av->robot[n].tx[1], av->robot[n].ty[1], av->robot[n].tx[2], av->robot[n].ty[2]);
        p.drawLine(av->robot[n].tx[2], av->robot[n].ty[2], av->robot[n].tx[3], av->robot[n].ty[3]);
        p.drawLine(av->robot[n].tx[3], av->robot[n].ty[3], av->robot[n].tx[1], av->robot[n].ty[1]);
        //setcolor(7);
        p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[5], av->robot[n].ty[5]);
        //setcolor(8);
        if ((av->show_arcs) && (av->robot[n].arc_count > 0)) {
            p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[6], av->robot[n].ty[6]);
            p.drawLine(av->robot[n].tx[4], av->robot[n].ty[4], av->robot[n].tx[7], av->robot[n].ty[7]);
            if (av->robot[n].scanrange < 1500) {
                p.drawArc(av->robot[n].tx[4], av->robot[n].ty[4], (int)round(av->robot[n].scanrange * atr2var::screen_scale), (int)round(av->robot[n].scanrange * atr2var::screen_scale), av->robot[n].startarc, av->robot[n].endarc);
            }
        }
        if ((av->show_arcs) && (av->robot[n].sonar_count > 0)) {
            p.drawEllipse(av->robot[n].tx[4], av->robot[n].ty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
        }
    }

    p.restore();

    //p->end();
}
