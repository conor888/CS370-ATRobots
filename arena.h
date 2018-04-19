//
// Created by conor on 3/20/2018.
//

#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include "atr2var.h"
#include "atr2.h"
#include <QPixmap>

class arena : public QWidget
{
Q_OBJECT

public:
    arena(atr2var* avtemp, QWidget *parent = 0);
    ~arena();

    void update_robot(int rn);
    void update_missile(int mn);
    void update_mine(int rn, int mn);
    void delete_robot(int rn);

private:
    void paintEvent(QPaintEvent *event) override;
    atr2var *av;

    //QPainter *m;

    QPixmap **pix = new QPixmap*[36];
    /*
     * PIXMAP INFO:
     * pix[0] - pix[31]: robots #0-31
     * pix[32]: all robots together
     * pix[33]: missiles
     * pix[34]: mines
     * pix[35]: black
    */

signals:
    void donePainting();
    void draw_robot(int rn);
    void do_missile(int mn);

};

#endif // ARENA_H
