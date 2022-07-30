#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QPen>
#include <QPointF>
#include <QRandomGenerator>

class ball : public QObject
{
    Q_OBJECT
  public:
    explicit ball(qreal, qreal, QObject *parent = nullptr);
    QPen getStyle();
    QPointF getPos();

  private:
    qreal r;
    QPointF pos;
    QPen ball_style;

  signals:
};

#endif // BALL_H
