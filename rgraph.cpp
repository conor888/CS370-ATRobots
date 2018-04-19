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

    r = new QPixmap(154, 65);
}

void rgraph::update_graph() {
    QPainter p(r);

    if (n < av->num_robots) {
        p.fillRect(0, 0, 154, 65, QBrush(Qt::black));
        p.setPen(QPen(atr2func::robot_color(n), 1));
        p.setFont(*P2);

        if(av->robot[n].selected) {
            p.drawRect(0, 0, 153, 64);
        }

        //First row: Robot name and Wins
        p.drawText(QRect(2, 1, 70, 10), QString::fromStdString(av->robot[n].fn));
        p.drawText(QRect(79, 1, 154, 10), QString::fromStdString("Wins:" + atr2func::zero_pad(av->robot[n].wins, 4)));


        //Third and fourth rows: Armor and Heat bars
        p.drawText(QRect(10, 23, 20, 10), QString::fromStdString("A:"));
        if (av->robot[n].armor < 100) {
            p.fillRect(29, 24, 100, 6, atr2func::pascal_color(8));
        }
        if (av->robot[n].armor > 0) {
            p.fillRect(29, 24, av->robot[n].armor, 6, atr2func::robot_color(n));
        }

        p.drawText(QRect(10, 33, 20, 10), QString::fromStdString("H:"));
        p.fillRect(29, 34, 100, 6, atr2func::pascal_color(8));
        if (av->robot[n].heat > 5) {
            p.fillRect(29, 34, (int)std::round((double)av->robot[n].heat / 5.0), 6, atr2func::robot_color(n));
        }


        //Sixth row: Error
        p.drawText(QRect(10, 55, 50, 10), QString::fromStdString("Error:"));
        p.setPen(QPen(atr2func::pascal_color(8)));
        p.drawText(QRect(65, 55, 40, 10), QString::fromStdString("None"));

        //Second row: Robot MSG
        p.setPen(QPen(atr2func::pascal_color(atr2func::robot_color_i(n) & 7)));
        p.drawText(QRect(2, 11, 154, 10), QString::fromStdString(av->robot[n].name));


        //Fifth row: Kills and Deaths
        p.drawText(QRect(10, 45, 50, 10), QString::fromStdString("K:" + atr2func::zero_pad(av->robot[n].kills, 4)));
        p.drawText(QRect(79, 45, 50, 10), QString::fromStdString("D:" + atr2func::zero_pad(av->robot[n].deaths, 4)));

        this->update();

    } else {
        p.fillRect(0, 0, 154, 65, QBrush(atr2func::pascal_color(8)));
        //p.setBrush(QBrush(atr2func::pascal_color(8), 1));
        p.fillRect(0, 0, 154, 65, Qt::Dense4Pattern);
    }

}

void rgraph::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawPixmap(0, 0, *r);
}
