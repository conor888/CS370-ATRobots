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

    setWindowTitle(QString::fromStdString("ATR2"));
    //resize(470, 470);
    setFixedSize(470, 470);

    av = avtemp;

    for (int i = 0; i < 34; i++) {
        pix[i] = new QPixmap(470, 470);
        pix[i]->fill(QColor(0, 0, 0, 0));
    }
}

void arena::update_vars(int nn, int new_target) {
    n = nn;
    update_target = new_target;
}

void arena::update_robot(int rn) {
    pix[rn]->fill(QColor(0,0,0,0));
    QPainter p(pix[rn]);

    //setcolor(robot_color(n) & 7);
    if (av->robot[rn].shields_up) {
        p.drawEllipse(av->robot[rn].tx[4], av->robot[rn].ty[4], atr2var::robot_scale, atr2var::robot_scale);
    }
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
            //p.setPen(QPen(QColor(0,0,255), 1));
            p.drawArc(av->robot[0].tx[4] - (av->robot[0].scanrange  * atr2var::screen_scale), //x
                      av->robot[0].ty[4] - (av->robot[0].scanrange  * atr2var::screen_scale), //y
                      (int)round(av->robot[0].scanrange * atr2var::screen_scale * 2), //h
                      (int)round(av->robot[0].scanrange * atr2var::screen_scale * 2), //w
                      av->robot[0].startarc * 16, //startArc
                      (av->robot[0].endarc - av->robot[0].startarc) * 16); //spanArc
        }
    }
    if ((av->show_arcs) && (av->robot[rn].sonar_count > 0)) {
        p.drawEllipse(av->robot[rn].tx[4], av->robot[rn].ty[4], (int)round(atr2var::max_sonar * atr2var::screen_scale), (int)round(atr2var::max_sonar * atr2var::screen_scale));
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

    setWindowTitle(QString::fromStdString("ATR2 | Match: " + std::to_string(av->played) + "/" + std::to_string(av->matches)
                                                         + " - Cycle: " + std::to_string(av->game_cycle) + "/" + std::to_string(av->game_limit / 1000) + "k - Delay (ms): " + std::to_string(av->game_delay)));

    QPainter p(this);

    p.setBrush(Qt::NoBrush);

    p.save();

    p.drawPixmap(0, 0, *pix[32]);
    p.drawPixmap(0, 0, *pix[33]);

    p.setPen(QPen(QColor(0,0,255), 1));

    /*QPointF const A(av->robot[0].tx[6], av->robot[0].ty[6]);
    QPointF const B(av->robot[0].tx[7], av->robot[0].ty[7]);
    QPointF const C(av->robot[0].tx[4], av->robot[0].ty[4]);
    double  const radius(av->robot[0].scanrange * atr2var::screen_scale);

    QRectF const r(C.x() - radius, C.y() - radius, radius * 2, radius * 2);
    double const startAngle = 16 * atan2(A.y() - C.y(), A.x() - C.x()) * 180.0 / M_PI;
    double const endAngle   = 16 * atan2(B.y() - C.y(), B.x() - C.x()) * 180.0 / M_PI;
    double const spanAngle = endAngle - startAngle;
    p.drawArc(r, startAngle, spanAngle);*/
    /*p.drawArc(av->robot[0].tx[4] - (av->robot[0].scanrange  * atr2var::screen_scale), //x
              av->robot[0].ty[4] - (av->robot[0].scanrange  * atr2var::screen_scale), //y
              (int)round(av->robot[0].scanrange * atr2var::screen_scale * 2), //h
              (int)round(av->robot[0].scanrange * atr2var::screen_scale * 2), //w
              av->robot[0].startarc * 16, //startArc
              (av->robot[0].endarc - av->robot[0].startarc) * 16); //spanArc*/

    p.restore();

    //p->end();

    //emit donePainting();
}

void arena::keyPressEvent(QKeyEvent *event){
    if ((event->key() == Qt::Key_Equal) || (event->key() == Qt::Key_Plus)){
        switch(av->game_delay) {
            case 0:
                av->game_delay = 1;
                break;
            case 1:
                av->game_delay = 5;
                break;
            case 5:
                av->game_delay = 10;
                break;
            case 10:
                av->game_delay = 15;
                break;
            case 15:
                av->game_delay = 20;
                break;
            case 20:
                av->game_delay = 30;
                break;
            case 30:
                av->game_delay = 40;
                break;
            case 40:
                av->game_delay = 50;
                break;
            case 50:
                av->game_delay = 60;
                break;
            case 60:
                av->game_delay = 75;
                break;
            case 75:
                av->game_delay = 100;
                break;
            case 100:
                break;
            default:
                av->game_delay = 1;
        }
    }
    else if ((event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_Underscore)){
        switch(av->game_delay) {
            case 0:
                break;
            case 1:
                av->game_delay = 0;
                break;
            case 5:
                av->game_delay = 1;
                break;
            case 10:
                av->game_delay = 5;
                break;
            case 15:
                av->game_delay = 10;
                break;
            case 20:
                av->game_delay = 15;
                break;
            case 30:
                av->game_delay = 20;
                break;
            case 40:
                av->game_delay = 30;
                break;
            case 50:
                av->game_delay = 40;
                break;
            case 60:
                av->game_delay = 50;
                break;
            case 75:
                av->game_delay = 60;
                break;
            case 100:
                av->game_delay = 75;
                break;
            default:
                av->game_delay = 1;
        }
    } else if (event->key() == Qt::Key_Space) {
        if (av->game_paused == false) {
            av->game_paused = true;
        } else {
            av->game_paused = false;
        }
    }
}

arena::~arena() {
    exit(0);
}
