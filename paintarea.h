#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainterPath>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void init();
    void drawPix(QPixmap *, QPainterPath *, QPen);
    void moveEvent();
    void paint(QPixmap *);

private:
    QPainter *p;
    QPainterPath border;
    QPen border_style;
    QPixmap *target_pix;

signals:
    void hitBorder();
};

#endif // PAINTAREA_H
