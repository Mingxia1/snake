#include "ball.h"

ball::ball(qreal width, qreal height, QObject *parent)
    : QObject{parent}
{
    r = 5;
    pos.setX(QRandomGenerator::global()->generateDouble() * width);
    pos.setY(QRandomGenerator::global()->generateDouble() * height);
}
