#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPen>
#include <QPainterPath>
#include <QColor>
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
    QPen getStyle(int);
    QPointF getStartPos();
    QPointF getEndPos();
    void setStartPos(const QPointF &);
    void setEndPos(const QPointF &);
    void setEndPosX(qreal);
    void setEndPosY(qreal);
    qreal getSpeed();
    qreal getAngleSpeed();
    qreal getRadAngel();
    void rotate(int);
    void setPath();
    QPainterPath getPath();
    void snakeMove();
    void setColor(QColor);

private:
    QPen snake_style, snake_dis_style;
    QPointF startPos, endPos;
    qreal speed;
    qreal angle;
    qreal angleSpeed;
    qreal length;
    QPainterPath snake_path;
    QList<QPainterPath> snake_path_list;

public slots:
    void rotateRight();
    void rotateLeft();

signals:
};

#endif // SNAKE_H
