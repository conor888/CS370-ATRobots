#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "atr2var.h"
#include "cgraph.h"
#include "rgraph.h"
#include <QPixmap>

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(atr2var* avtemp, cgraph* cyclegtemp, rgraph** rgraphstemp, QWidget *parent = nullptr);

private:
    void init_window();
    void box(int x1, int y1, int x2, int y2, QPixmap* canvas);
    void hole(int x1, int y1, int x2, int y2, QPixmap* canvas);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    atr2var *av;
    cgraph* cycleg;
    rgraph** rgraphs;
    QPixmap *windowborder;

public slots:
    void repaint_now();

signals:
    void force_repaint();
};

#endif // WINDOW_H
