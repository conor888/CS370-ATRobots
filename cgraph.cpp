#include "cgraph.h"
#include <QPainter>
#include <QFontDatabase>
#include "atr2func.h"

cgraph::cgraph(atr2var* avtemp, QWidget *parent) : QWidget(parent)
{
    setFixedSize(154, 44);

    QFontDatabase::addApplicationFont(":/fonts/Extra/PressStart2P.ttf");
    P2 = new QFont("Press Start 2P");
    P2->setStyleStrategy(QFont::NoAntialias);
    P2->setPixelSize(8);
    //P2->setWeight(QFont::Bold);
    //P2->setHintingPreference(QFont::PreferNoHinting);
    //P2->setStyleHint(QFont::TypeWriter);

    av = avtemp;

}

void cgraph::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.save();

    p.fillRect(0, 0, 154, 44, QBrush(Qt::black));
    p.setPen(QPen(atr2func::robot_color(6), 1));
    p.setFont(*P2);
    p.drawText(QRect(2, 2, 154, 10), QString::fromStdString("Delay:   " + atr2func::zero_pad(av->game_delay, 3)));

    p.drawText(QRect(2, 12, 154, 20), QString::fromStdString("Cycle:   " + atr2func::zero_pad(av->game_cycle - 1, 9)));
    p.drawText(QRect(2, 22, 154, 30), QString::fromStdString("Limit:   " + atr2func::zero_pad(av->game_limit, 9)));
    p.drawText(QRect(2, 32, 154, 30), QString::fromStdString("Match:   " + std::to_string(av->played) + "/" + std::to_string(av->matches)));

    p.restore();

}
