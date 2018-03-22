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

    void update_vars(int n);

private:
    void paintEvent(QPaintEvent *event) override;
    atr2var *av;
    int n = 0;
};

#endif // ARENA_H