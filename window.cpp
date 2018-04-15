#include "window.h"
#include <QKeyEvent>
#include <QPainter>
#include "atr2func.h"

window::window(atr2var* avtemp, cgraph* cyclegtemp, QWidget *parent) : QWidget(parent)
{
    setFixedSize(640, 480);

    av = avtemp;
    cycleg = cyclegtemp;

    windowborder = new QPixmap(640, 480);
    windowborder->fill(QColor(168, 168, 168));
    init_window();
}

void window::init_window() {

    box(0, 0, 639, 479, windowborder);
    hole(4, 4, 475, 475, windowborder);

    hole(480, 4, 635, 70, windowborder);
    hole(480, 74, 635, 140, windowborder);
    hole(480, 144, 635, 210, windowborder);
    hole(480, 214, 635, 280, windowborder);
    hole(480, 284, 635, 350, windowborder);
    hole(480, 354, 635, 420, windowborder);

    hole(480, 430, 635, 475, windowborder);

}

void window::box(int x1, int y1, int x2, int y2, QPixmap* canvas) {
    QPainter p(canvas);
    p.save();

    p.setPen(QPen(atr2func::pascal_color(15), 1));
    p.drawLine(x1, y1, x2 - 1, y1);
    p.drawLine(x1, y1, x1, y2 - 1);

    p.setPen(QPen(atr2func::pascal_color(8), 1));
    p.drawLine(x1 + 1, y2, x2, y2);
    p.drawLine(x2, y1 + 1, x2, y2);

    p.restore();
}

void window::hole(int x1, int y1, int x2, int y2, QPixmap* canvas) {
    QPainter p(canvas);
    p.save();

    p.setPen(QPen(atr2func::pascal_color(8), 1));
    p.drawLine(x1, y1, x2 - 1, y1);
    p.drawLine(x1, y1, x1, y2 - 1);

    p.setPen(QPen(atr2func::pascal_color(15), 1));
    p.drawLine(x1 + 1, y2, x2, y2);
    p.drawLine(x2, y1 + 1, x2, y2);

    p.setPen(QPen(atr2func::pascal_color(7), 1));
    p.drawPoint(x1, y2);
    p.drawPoint(x2, y1);

    p.restore();
}

void window::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.save();

    p.drawPixmap(0, 0, *windowborder);

    p.restore();

}


void window::keyPressEvent(QKeyEvent *event){
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
    } else if (event->key() == Qt::Key_M) {
        repaint();
    }

    cycleg->update();
}
