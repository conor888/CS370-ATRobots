#include "window.h"
#include <QKeyEvent>

window::window(atr2var* avtemp, cgraph* cyclegtemp, QWidget *parent) : QWidget(parent)
{
    setFixedSize(640, 480);

    av = avtemp;
    cycleg = cyclegtemp;
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
