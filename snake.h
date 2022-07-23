#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPen>
#include <QPainterPath>
#include <QColor>
#include <QColormap>
#include <QImage>
#define LEFT 1
#define RIGHT 2
#define PI 3.1416
#define WHITE 1
#define BLACK 2

class snake : public QObject
{
    Q_OBJECT
public:
    explicit snake(QObject *parent = nullptr);
    void init(double, double);
    QPen getStyle();
    QPointF getStartPos();
    QPointF getEndPos();
    void setStartPos(const QPointF &);
    void setEndPos(const QPointF &);
    void setEndPosX(qreal);
    void setEndPosY(qreal);
    void setPath();
    void setColor(QColor);
    qreal getSpeed();
    qreal getAngleSpeed();
    qreal getRadAngel();
    QPainterPath *getPath();
    void rotate(int);
    void snakeMove();
    void eatBall();

private:
    QPen snake_style;
    QPointF startPos, endPos;
    qreal speed;
    qreal angle;
    qreal angleSpeed;
    qreal length;
    QPainterPath snake_path;
    QList<QPainterPath> snake_path_list;
    QRectF head;
    qreal width, height;

public slots:
    void rotateRight();
    void rotateLeft();

signals:
    void hitBody();
    void hitBorder();
};

#endif // SNAKE_H
