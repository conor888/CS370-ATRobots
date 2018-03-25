//
// Created by conor on 3/20/2018.
//

#include <QtWidgets>
#include "arena.h"
#include "atr2.h"
#include "atr2func.h"
#include <QKeyEvent>
#include <QPixmap>

arena::arena(atr2var* avtemp, QWidget *parent) : QWidget(parent)
{
    //connect(this, SIGNAL(doneDrawingRobots), this, SLOT(update()));

    //this->setUpdatesEnabled(false);

    setWindowTitle(tr("ATR2"));
    resize(470, 470);
    //resize(940, 940);

    av = avtemp;

    for (int i = 0; i < 33; i++) {
        pix[i] = new QPixmap(470, 470);
        pix[i]->fill(QColor(0, 0, 0, 0));
    }

    //clear = new QPixmap(470, 470);
    
    //p = new QPainter(this);
    //p->setBackgroundMode(Qt::NoBackground);
}

void arena::update_vars(int nn, int new_target) {
    n = nn;
    update_target = new_target;
}

void arena::update_missile(double new_llx, double new_lly) {
    llx = new_llx;
    lly = new_lly;
}

void arena::clear_arena() {
    QPainter p(this);

    p.save();
    p.restore();
}

void arena::update_robot(int rn) {
    //this->setUpdatesEnabled(false);
    QPixmap clear(470, 470);
    clear.fill(QColor(0, 0, 0, 0));
    pix[rn]->swap(clear);
    QPainter p(pix[rn]);

    /*p.setPen(QPen(Qt::black, 18));

    //erase
    /*if (n == 0) {
        p.fillRect(0, 0, 940, 940, Qt::black);
    }*/
    /*if (av->robot[n].lshields) {
        p.drawEllipse(av->robot[n].ltx[4], av->robot[n].lty[4], atr2var::robot_scale, atr2var::robot_scale);
    }
    if (av->robot[n].arc_count > 0) {
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
    }*/


    if (av->robot[rn].armor > 0) {
        //setcolor(robot_color(n) & 7);
        if (av->robot[rn].shields_up) {
            p.drawEllipse(av->robot[rn].tx[4], av->robot[rn].ty[4], atr2var::robot_scale, atr2var::robot_scale);
        }
        //setcolor(robot_color(n));
        p.setPen(QPen(atr2func::robot_color(rn), 2));
        p.drawLine(av->robot[rn].tx[1], av->robot[rn].ty[1], av->robot[rn].tx[2], av->robot[rn].ty[2]);
        p.drawLine(av->robot[rn].tx[2], av->robot[rn].ty[2], av->robot[rn].tx[3], av->robot[rn].ty[3]);
        p.drawLine(av->robot[rn].tx[3], av->robot[rn].ty[3], av->robot[rn].tx[1], av->robot[rn].ty[1]);
        //setcolor(7);
        p.setPen(QPen(QColor(200,200,200), 1));
        p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[5], av->robot[rn].ty[5]);
        //setcolor(8);
        p.setPen(QPen(QColor(100,100,100), 1));
        if ((av->show_arcs) && (av->robot[rn].arc_count > 0)) {
            p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[6], av->robot[rn].ty[6]);
            p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[7], av->robot[rn].ty[7]);
            if (av->robot[rn].scanrange < 1500) {
                p.drawArc(av->robot[rn].tx[4], av->robot[rn].ty[4], (int)round(av->robot[rn].scanrange * atr2var::screen_scale),
                        (int)round(av->robot[rn].scanrange * atr2var::screen_scale), av->robot[rn].startarc, av->robot[rn].endarc);
            }
        }
        if ((av->show_arcs) && (av->robot[rn].sonar_count > 0)) {
            p.drawEllipse(av->robot[rn].tx[4], av->robot[rn].ty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
        }
    }

    QPainter pp(pix[32]);
    pp.fillRect(0, 0, 470, 470, Qt::black);
    for (int i = 0; i < av->num_robots; i++) {
        pp.drawPixmap(0, 0, *pix[i]);
    }

    //this->setUpdatesEnabled(true);
    this->update();
}

void arena::paintEvent(QPaintEvent *)
{
    //int side = qMin(width(), height());
    //QPainter p(this);
    //p->setRenderHint(QPainter::Antialiasing);
    //p->translate(width() / 2, height() / 2);
    //p->scale(side / 200.0, side / 200.0);

    QPainter p(this);

    p.setBrush(Qt::NoBrush);

    p.save();

    //p.fillRect(0, 0, 470, 470, Qt::black);
    p.drawPixmap(0, 0, *pix[32]);

    if (update_target == 0) { //clear arena
        p.fillRect(0, 0, 470, 470, Qt::black);
    } else if (update_target == 1) { //draw robot

        //p.fillRect(0, 0, 470, 470, Qt::black);
        //for (int i = 0; i < num_robots; i++) {
        //    p.drawPixmap(0, 0, *pix[i]);
        //}

    } else if (update_target == 2) { //missile
        //erase
        p.setPen(QPen(Qt::black, 8));

        p.drawLine((int)round(llx * atr2var::screen_scale) + atr2var::screen_x,
                   (int)round(lly * atr2var::screen_scale) + atr2var::screen_y,
                   (int)round(av->missile[n].lx * atr2var::screen_scale + atr2var::screen_x),
                   (int)round(av->missile[n].ly * atr2var::screen_scale) + atr2var::screen_y);

        //draw new
        if (av->missile[n].a == 1) {
            if (av->missile[n].mult > av->robot[av->missile[n].source].shotstrength) {
                //setcolor(14+(game_cycle & 1))
            }
            p.setPen(QPen(Qt::white, 1));

            p.drawLine((int)round(av->missile[n].x * atr2var::screen_scale) + atr2var::screen_x,
                       (int)round(av->missile[n].y * atr2var::screen_scale) + atr2var::screen_y,
                       (int)round(av->missile[n].lx * atr2var::screen_scale) + atr2var::screen_x,
                       (int)round(av->missile[n].ly * atr2var::screen_scale) + atr2var::screen_y);
        }

        else if (av->missile[n].a == 2) {
            p.setPen(QPen(Qt::black, 8));
            p.drawEllipse((int)round(av->missile[n].x * atr2var::screen_scale) + atr2var::screen_x,
                          (int)round(av->missile[n].y * atr2var::screen_scale) + atr2var::screen_y,
                          av->missile[n].lrad * 2, av->missile[n].lrad * 2);

            if (av->missile[n].a > 0) {
                p.setPen(QPen(Qt::white, 1));
                p.drawEllipse((int)round(av->missile[n].x * atr2var::screen_scale) + atr2var::screen_x,
                              (int)round(av->missile[n].y * atr2var::screen_scale) + atr2var::screen_y,
                              av->missile[n].rad * 2, av->missile[n].rad * 2);
            }
        }
    }

    p.restore();

    //p->end();

    emit donePainting();
}

void arena::keyPressEvent(QKeyEvent *event){
    if ((event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_Plus)){
        av->game_delay++;
    }
    else if ((event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_Underscore)){
        av->game_delay--;
    }
}

arena::~arena() {
    exit(0);
}
