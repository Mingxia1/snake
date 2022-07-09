#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QKeyEvent>
#include "snake.h"
#include <QTimer>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void init(snake *);
    void drawPix();
    QPointF getCentre();
    void ifHitBorder();

private:
    QPixmap *pix;
    QSize box;
    QPainter *p;
    snake *playerSnake;
    QTimer *draw_timer;
    QTimer *rotate_right_timer;
    QTimer *rotate_left_timer;
    QPainterPath border;
    QPainterPath last_path;
    QPen border_style;

signals:
    void hitBorder();

private slots:
    void moveEvent();
};

#endif // PAINTAREA_H
