#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "atr2var.h"
#include "cgraph.h"

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(atr2var* avtemp, cgraph* cyclegtemp, QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent * event);
    atr2var *av;
    cgraph* cycleg;
};

#endif // WINDOW_H
