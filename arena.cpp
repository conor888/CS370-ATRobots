//
// Created by conor on 3/20/2018.
//

#include <QtWidgets>
#include "arena.h"

arena::arena(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("ATR2"));
    resize(1000, 1000);
}

void arena::update_vars(atr2var av, int nn) {
    //ag = av;
    n = nn;
}

void arena::paintEvent(QPaintEvent *)
{
    int side = qMin(width(), height());
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width() / 2, height() / 2);
    p.scale(side / 200.0, side / 200.0);

    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);


    p.save();

    if (ag.robot[n].lshields) {
        p.drawEllipse(ag.robot[n].ltx[4], ag.robot[n].lty[4], atr2var::robot_scale, atr2var::robot_scale);
    }
    if (ag.robot[n].arc_count < 0) {
        p.drawLine(ag.robot[n].ltx[4], ag.robot[n].lty[4], ag.robot[n].ltx[6], ag.robot[n].lty[6]);
        p.drawLine(ag.robot[n].ltx[4], ag.robot[n].lty[4], ag.robot[n].ltx[7], ag.robot[n].lty[7]);
        if (ag.robot[n].scanrange < 1500) {
            p.drawArc(ag.robot[n].ltx[4], ag.robot[n].lty[4], (int)round(ag.robot[n].scanrange * atr2var::screen_scale), (int)round(ag.robot[n].scanrange * atr2var::screen_scale), ag.robot[n].lstartarc, ag.robot[n].lendarc);
        }
    }
    if (ag.robot[n].sonar_count > 0) {
        p.drawEllipse(ag.robot[n].ltx[4], ag.robot[n].lty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
    }
    if (ag.robot[n].armor > 0) { //only erase body if still alive, that way we leave a "corpse" when dead
        p.drawLine(ag.robot[n].ltx[1], ag.robot[n].lty[1], ag.robot[n].ltx[2], ag.robot[n].lty[2]);
        p.drawLine(ag.robot[n].ltx[2], ag.robot[n].lty[2], ag.robot[n].ltx[3], ag.robot[n].lty[3]);
        p.drawLine(ag.robot[n].ltx[3], ag.robot[n].lty[3], ag.robot[n].ltx[1], ag.robot[n].lty[1]);
        p.drawLine(ag.robot[n].ltx[4], ag.robot[n].lty[4], ag.robot[n].ltx[5], ag.robot[n].lty[5]);
    }

    if (ag.robot[n].armor > 0) {
        //setcolor(robot_color(n) & 7);
        if (ag.robot[n].shields_up) {
            p.drawEllipse(ag.robot[n].tx[4], ag.robot[n].ty[4], atr2var::robot_scale, atr2var::robot_scale);
        }
        //setcolor(robot_color(n));
        p.drawLine(ag.robot[n].tx[1], ag.robot[n].ty[1], ag.robot[n].tx[2], ag.robot[n].ty[2]);
        p.drawLine(ag.robot[n].tx[2], ag.robot[n].ty[2], ag.robot[n].tx[3], ag.robot[n].ty[3]);
        p.drawLine(ag.robot[n].tx[3], ag.robot[n].ty[3], ag.robot[n].tx[1], ag.robot[n].ty[1]);
        //setcolor(7);
        p.drawLine(ag.robot[n].tx[4], ag.robot[n].ty[4], ag.robot[n].tx[5], ag.robot[n].ty[5]);
        //setcolor(8);
        if ((ag.show_arcs) && (ag.robot[n].arc_count > 0)) {
            p.drawLine(ag.robot[n].tx[4], ag.robot[n].ty[4], ag.robot[n].tx[6], ag.robot[n].ty[6]);
            p.drawLine(ag.robot[n].tx[4], ag.robot[n].ty[4], ag.robot[n].tx[7], ag.robot[n].ty[7]);
            if (ag.robot[n].scanrange < 1500) {
                p.drawArc(ag.robot[n].tx[4], ag.robot[n].ty[4], (int)round(ag.robot[n].scanrange * atr2var::screen_scale), (int)round(ag.robot[n].scanrange * atr2var::screen_scale), ag.robot[n].startarc, ag.robot[n].endarc);
            }
        }
        if ((ag.show_arcs) && (ag.robot[n].sonar_count > 0)) {
            p.drawEllipse(ag.robot[n].tx[4], ag.robot[n].ty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
        }
    }

    p.restore();
}
