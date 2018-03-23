//
// Created by conor on 3/20/2018.
//

#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include "atr2var.h"
#include "atr2.h"

class arena : public QWidget
{
Q_OBJECT

public:
    arena(atr2var* avtemp, QWidget *parent = 0);

    void update_vars(int nn, int new_target);
    void update_missile(double new_llx, double new_lly);
    void clear_arena();

private:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent * event);
    atr2var *av;
    int n = 0;
    int update_target = 0;

    //missile coords
    double llx = 0.0, lly = 0.0;
};

#endif // ARENA_H