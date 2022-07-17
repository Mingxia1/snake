#include "snake.h"
#include <cmath>
#define ANGLE angle *PI / 180

snake::snake(QObject *parent)
    : QObject{parent}
{
    snake_style.setStyle(Qt::SolidLine);
    snake_style.setCapStyle(Qt::RoundCap);
    snake_style.setJoinStyle(Qt::RoundJoin);
    snake_style.setWidth(10);
    snake_style.setColor(Qt::black);
    snake_dis_style.setStyle(Qt::SolidLine);
    snake_dis_style.setCapStyle(Qt::RoundCap);
    snake_dis_style.setJoinStyle(Qt::RoundJoin);
    snake_dis_style.setWidth(10);
    snake_dis_style.setColor(Qt::white);
}

void snake::init(double x, double y)
{
    startPos.setX(x);
    startPos.setY(y);
    endPos = startPos;
    speed = 0.5;
    angle = 0;
    angleSpeed = 1.5;
    length = 250;
}

QPen snake::getStyle(int a)
{
    if (a == BLACK)
        return snake_style;
    else
        return snake_dis_style;
}

QPointF snake::getStartPos() //目前无用
{
    return startPos;
}

QPointF snake::getEndPos()
{
    return endPos;
}

void snake::setStartPos(const QPointF &tempPoint)
{
    startPos = tempPoint;
}

void snake::setEndPos(const QPointF &tempPoint) //目前无用
{
    endPos = tempPoint;
}

void snake::setEndPosX(qreal x) //目前无用
{
    endPos.setX(x);
}

void snake::setEndPosY(qreal y) //目前无用
{
    endPos.setY(y);
}

qreal snake::getSpeed() //目前无用
{
    return speed;
}

qreal snake::getAngleSpeed() //目前无用
{
    return angleSpeed;
}

void snake::rotate(int flag)
{
    if (flag == LEFT)
    {
        angle += angleSpeed;
    }
    if (flag == RIGHT)
    {
        angle -= angleSpeed;
    }
    if (angle >= 360)
    {
        angle = fmod(angle, 360);
    }
    else if (angle < 0)
    {
        angle = fmod(angle, 360);
    }
}

void snake::rotateRight()
{
    rotate(RIGHT);
}

void snake::rotateLeft()
{
    rotate(LEFT);
}

void snake::setPath() //目前无用
{
    QPainterPath tempPath;
    tempPath.moveTo(startPos);
    tempPath.lineTo(endPos);
    snake_path_list << tempPath;
}

QPainterPath snake::getPath()
{
    snake_path.clear();
    if (cos(ANGLE) > 0 && sin(ANGLE) > 0)
        head = QRectF(endPos.x() + 5 * cos(ANGLE), endPos.y() - 5 * sin(ANGLE) - 5, 0.5, 0.5);
    else if (cos(ANGLE) < 0 && sin(ANGLE) > 0)
        head = QRectF(endPos.x() + 5 * cos(ANGLE) - 5, endPos.y() - 5 * sin(ANGLE) - 5, 0.5, 0.5);
    else if (cos(ANGLE) < 0 && sin(ANGLE) < 0)
        head = QRectF(endPos.x() + 5 * cos(ANGLE) - 5, endPos.y() - 5 * sin(ANGLE), 0.5, 0.5);
    else if (cos(ANGLE) > 0 && sin(ANGLE) < 0)
        head = QRectF(endPos.x() + 5 * cos(ANGLE), endPos.y() - 5 * sin(ANGLE), 0.5, 0.5);
    QList<QPainterPath>::const_iterator i = snake_path_list.cbegin();
    for (; i != snake_path_list.cend(); i++)
    {
        if (i->intersects(head))
            emit hitBody();
        snake_path.addPath(*i);
    }
    return snake_path;
}

void snake::snakeMove()
{
    endPos.setX(startPos.x() + cos(ANGLE) * speed);
    endPos.setY(startPos.y() - sin(ANGLE) * speed);
    QPainterPath tempPath;
    tempPath.moveTo(startPos);
    tempPath.lineTo(endPos);
    if (snake_path.length() == length)
    {
        snake_path_list << tempPath;
        snake_path_list.removeFirst();
        startPos = endPos;
    }
    else if (snake_path.length() < length)
    {
        snake_path_list << tempPath;
        startPos = endPos;
    }
    else if (snake_path.length() > length)
    {
        snake_path_list.removeFirst();
    }
}

void snake::setColor(QColor a)
{
    snake_style.setColor(a);
}

void snake::ifHitBorder(int width, int height)
{
    if (endPos.x() <= 15 || endPos.x() >= width - 15 || endPos.y() <= 15 || endPos.y() >= height - 15)
        emit hitBorder();
}