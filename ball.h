#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QPointF>
#include <QRandomGenerator>

class ball : public QObject
{
    Q_OBJECT
public:
    explicit ball(qreal, qreal, QObject *parent = nullptr);

private:
    qreal r;
    QPointF pos;

signals:
};

#endif // BALL_H
