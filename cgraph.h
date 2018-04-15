#ifndef CGRAPH_H
#define CGRAPH_H

#include <QWidget>
#include "atr2var.h"

class cgraph : public QWidget
{
    Q_OBJECT
public:
    explicit cgraph(atr2var* avtemp, QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event) override;

    QFont *P2;
    atr2var *av;
};

#endif // RGRAPH_H
