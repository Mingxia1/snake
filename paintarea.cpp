#include "paintarea.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>

PaintArea::PaintArea(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
    border_style.setWidth(20);
    border_style.setColor(Qt::black);
    border_style.setStyle(Qt::SolidLine);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
}

void PaintArea::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Right)
    {
        rotate_right_timer = new QTimer;
        rotate_right_timer->start(1);
        connect(rotate_right_timer, SIGNAL(timeout()), playerSnake, SLOT(rotateRight()));
    }
    if (e->key() == Qt::Key_Left)
    {
        rotate_left_timer = new QTimer;
        rotate_left_timer->start(1);
        connect(rotate_left_timer, SIGNAL(timeout()), playerSnake, SLOT(rotateLeft()));
    }
}

void PaintArea::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Right)
    {
        rotate_right_timer->stop();
    }
    if (e->key() == Qt::Key_Left)
    {
        rotate_left_timer->stop();
    }
}

void PaintArea::drawPix()
{
    p->begin(pix);
    p->setPen(playerSnake->getStyle(WHITE));
    p->drawPath(last_path);
    p->setPen(playerSnake->getStyle(BLACK));
    last_path = playerSnake->getPath();
    p->drawPath(playerSnake->getPath());
    p->end();
    playerSnake->setStartPos(playerSnake->getEndPos());
}

void PaintArea::init(snake *snake)
{
    playerSnake = snake;
    pix = new QPixmap(size());
    pix->fill(Qt::white);
    p = new QPainter;
    border.addRect(rect());
    p->begin(pix);
    p->setPen(border_style);
    p->drawPath(border);
}

void PaintArea::moveEvent()
{
    playerSnake->snakeMove();
    drawPix();
    update();

    ifHitBorder();
}

QPointF PaintArea::getCentre() //目前无用
{
    QPointF tempPos;
    tempPos.setX(width() / 2);
    tempPos.setY(height() / 2);
    return tempPos;
}

void PaintArea::ifHitBorder()
{
    QPointF tempPos(playerSnake->getEndPos());
    if (tempPos.x() <= 15 || tempPos.x() >= width() - 15 || tempPos.y() <= 15 || tempPos.y() >= height() - 15)
        emit hitBorder();
}