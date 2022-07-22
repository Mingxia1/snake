#include "ball.h"

ball::ball(qreal width, qreal height, QObject *parent)
    : QObject{parent}
{
    r = 5;
    pos.setX(QRandomGenerator::global()->generateDouble() * (width - 20) + 15);
    pos.setY(QRandomGenerator::global()->generateDouble() * (height - 20) + 15);
    ball_style.setColor(Qt::black);
    ball_style.setCapStyle(Qt::RoundCap);
    ball_style.setStyle(Qt::SolidLine);
    ball_style.setWidth(10);
}

QPen ball::getStyle()
{
    return ball_style;
}

QPointF ball::getPos()
{
    return pos;
}
