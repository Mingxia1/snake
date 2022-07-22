#include "paintarea.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>

PaintArea::PaintArea(QWidget *parent)
    : QWidget{parent}
{
    border_style.setWidth(20);
    border_style.setColor(Qt::black);
    border_style.setStyle(Qt::SolidLine);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *target_pix);
}

void PaintArea::drawPix(QPixmap *pix, QPainterPath *path, QPen pen)
{
    p->begin(pix);
    p->setPen(border_style);
    p->drawPath(border);
    p->setPen(pen);
    p->drawPath(*path);
    p->end();
}

void PaintArea::drawBall(QPixmap *pix, QPointF pos, QPen pen)
{
    p->begin(pix);
    p->setPen(pen);
    p->drawPoint(pos);
    p->end();
}

void PaintArea::init()
{
    p = new QPainter;
    border.addRect(rect());
}

void PaintArea::paint(QPixmap *pix)
{
    target_pix = pix;
    update();
}