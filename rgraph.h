#ifndef RGRAPH_H
#define RGRAPH_H

#include <QWidget>
#include "atr2var.h"

class rgraph : public QWidget
{
    Q_OBJECT
public:
    explicit rgraph(int nn, atr2var* avtemp, QWidget *parent = nullptr);
    void update_graph();

private:
    void paintEvent(QPaintEvent *event) override;

    QFont *P2;
    int n;
    atr2var *av;

    QPixmap *r;
};

#endif // RGRAPH_H
