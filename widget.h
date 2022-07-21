#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include "snake.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void gameStart();

public slots:
    void gameOver();
    void timerEvent();

private:
    Ui::Widget *ui;
    snake *player_snake;
    QPixmap *pix;
    QTimer *rotate_right_timer;
    QTimer *rotate_left_timer;
};
#endif // WIDGET_H
