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
    //resize(470, 470);
    setFixedSize(470, 470);

    av = avtemp;

    for (int i = 0; i < 34; i++) {
        pix[i] = new QPixmap(470, 470);
        pix[i]->fill(QColor(0, 0, 0, 0));
    }

    //missiles = new QPixmap(470, 470);
    //missiles->fill(QColor(0, 0, 0, 0));
    
    //p = new QPainter(this);
    //p->setBackgroundMode(Qt::NoBackground);
}

void arena::update_vars(int nn, int new_target) {
    n = nn;
    update_target = new_target;
}

/*void arena::update_missile(double new_llx, double new_lly) {
    llx = new_llx;
    lly = new_lly;
}*/

void arena::clear_arena() {
    QPainter p(this);

    p.save();
    p.restore();
}

void arena::update_robot(int rn) {
    QPixmap clear(470, 470);
    clear.fill(QColor(0, 0, 0, 0));
    pix[rn]->swap(clear);
    QPainter p(pix[rn]);

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

    this->update();
}

void arena::update_missile(int mn) {
    if (mn == 3000) {
        pix[33]->fill(QColor(0,0,0,0));
    } else {
        QPainter p(pix[33]);
        if (av->missile[mn].a == 1) {
            if (av->missile[mn].mult > av->robot[av->missile[mn].source].shotstrength) {
                //setcolor(14+(game_cycle & 1))
            }
            p.setPen(QPen(Qt::white, 1));

            p.drawLine((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x,
                       (int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y,
                       (int)round(av->missile[mn].lx * atr2var::screen_scale) + atr2var::screen_x,
                       (int)round(av->missile[mn].ly * atr2var::screen_scale) + atr2var::screen_y);
        }

        else if (av->missile[mn].a == 2) {
            p.setPen(QPen(Qt::black, 8));
            p.drawEllipse((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x,
                          (int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y,
                          av->missile[mn].lrad * 2, av->missile[mn].lrad * 2);

            if (av->missile[mn].a > 0) {
                p.setPen(QPen(Qt::white, 1));
                p.drawEllipse((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x,
                              (int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y,
                              av->missile[mn].rad * 2, av->missile[mn].rad * 2);
            }
        }

        this->update();
    }
}

void arena::clear_missiles() {
    QPixmap clear(470, 470);
    clear.fill(QColor(0, 0, 0, 0));
    pix[33]->swap(clear);
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
    p.drawPixmap(0, 0, *pix[33]);

    if (update_target == 0) { //clear arena
        //p.fillRect(0, 0, 470, 470, Qt::black);
    } else if (update_target == 1) { //draw robot

        //p.fillRect(0, 0, 470, 470, Qt::black);
        //for (int i = 0; i < num_robots; i++) {
        //    p.drawPixmap(0, 0, *pix[i]);
        //}

    } else if (update_target == 2) { //missile



    }

    p.restore();

    //p->end();

    emit donePainting();
}

void arena::keyPressEvent(QKeyEvent *event){
    if ((event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_Plus)){
        av->game_delay++;
        //std::cout << "game delay is now " << av->game_delay << std::endl;
    }
    else if ((event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_Underscore)){
        av->game_delay--;
        //std::cout << "game delay is now " << av->game_delay << std::endl;
    }
}

arena::~arena() {
    exit(0);
}
