#include "rgraph.h"
#include <QPainter>
#include <QFontDatabase>
#include "atr2func.h"

rgraph::rgraph(int nn, atr2var* avtemp, QWidget *parent) : QWidget(parent)
{
    setFixedSize(154, 65);

    QFontDatabase::addApplicationFont(":/fonts/Extra/PressStart2P.ttf");
    P2 = new QFont("Press Start 2P");
    P2->setStyleStrategy(QFont::NoAntialias);
    P2->setPixelSize(8);
    //P2->setWeight(QFont::Bold);
    //P2->setHintingPreference(QFont::PreferNoHinting);
    //P2->setStyleHint(QFont::TypeWriter);

    n = nn;
    av = avtemp;

}

void rgraph::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.save();

    p.fillRect(0, 0, 154, 65, QBrush(Qt::black));
    p.setPen(QPen(atr2func::robot_color(n), 1));
    //3, 2, 62, 7
    p.setFont(*P2);
    p.drawText(QRect(2, 1, 62, 10), QString::fromStdString(av->robot[n].fn));
    p.drawText(QRect(80, 1, 154, 10), QString::fromStdString("Wins:" + atr2func::zero_pad(av->robot[n].wins, 4)));

    p.drawText(QRect(2, 10, 62, 20), QString::fromStdString("A:" + std::to_string(av->robot[n].armor)));
    p.drawText(QRect(2, 20, 62, 30), QString::fromStdString("H:" + std::to_string(av->robot[n].heat)));

    p.drawText(QRect(2, 57, 62, 64), QString::fromStdString("K:" + atr2func::zero_pad(av->robot[n].kills, 4)));
    p.drawText(QRect(62, 57, 122, 64), QString::fromStdString("D:" + atr2func::zero_pad(av->robot[n].deaths, 4)));

    p.restore();

}
