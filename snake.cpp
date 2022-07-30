#include "snake.h"
#include <cmath>
#define ANGLE angle *PI / 180

snake::snake(QObject *parent) : QObject{parent}
{
    speed = 0;
    angle = 0;
    angleSpeed = 0;
    length = 0;
    width = 0;
    height = 0;
    snake_style.setStyle(Qt::SolidLine);
    snake_style.setCapStyle(Qt::RoundCap);
    snake_style.setJoinStyle(Qt::RoundJoin);
    snake_style.setWidth(10);
    snake_style.setColor(Qt::black);
}

void snake::init(double _width, double _height)
{
    width = _width;
    height = _height;
    startPos.setX(_width / 2);
    startPos.setY(_height / 2);
    endPos = startPos;
    speed = 0.7;
    angle = 0;
    angleSpeed = 1.0;
    length = 200;
}

QPen snake::getStyle()
{
    return snake_style;
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
    if (angle >= 360 || angle < 0)
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

QPainterPath *snake::getPath()
{
    snake_path.clear();
    if (cos(ANGLE) > 0 && sin(ANGLE) > 0)
    {
        head = QRectF(endPos.x() + 5 * cos(ANGLE), endPos.y() - 5 * sin(ANGLE) - 5, 0.5, 0.5);
    }
    else if (cos(ANGLE) < 0 && sin(ANGLE) > 0)
    {
        head = QRectF(endPos.x() + 5 * cos(ANGLE) - 5, endPos.y() - 5 * sin(ANGLE) - 5, 0.5, 0.5);
    }
    else if (cos(ANGLE) < 0 && sin(ANGLE) < 0)
    {
        head = QRectF(endPos.x() + 5 * cos(ANGLE) - 5, endPos.y() - 5 * sin(ANGLE), 0.5, 0.5);
    }
    else if (cos(ANGLE) > 0 && sin(ANGLE) < 0)
    {
        head = QRectF(endPos.x() + 5 * cos(ANGLE), endPos.y() - 5 * sin(ANGLE), 0.5, 0.5);
    }
    QList<QPainterPath>::const_iterator i = snake_path_list.cbegin();
    for (; i != snake_path_list.cend(); i++)
    {
        if (i->intersects(head))
        {
            emit hitBody();
            return &snake_path;
        }
        snake_path.addPath(*i);
    }
    return &snake_path;
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
    //判断是否碰撞边界
    if (endPos.x() <= 15 || endPos.x() >= width - 15 || endPos.y() <= 15 || endPos.y() >= height - 15)
    {
        emit hitBorder();
    }
}

void snake::setColor(QColor a)
{
    snake_style.setColor(a);
}

void snake::eatBall()
{
    length += 30;
}