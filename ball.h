#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QPointF>

class ball : public QObject
{
    Q_OBJECT
public:
    explicit ball(QObject *parent = nullptr);
    void spawn();

private:
    qreal r;
    QPointF pos;

signals:
};

#endif // BALL_H
