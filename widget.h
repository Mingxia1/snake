#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <QPainter>
#include "snake.h"
#include "ball.h"

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
    void drawBall(QPointF, QPen);
    void drawSnake();
    void paintEvent(QPaintEvent *);
    void mainMenu();

public slots:
    void gameOver();
    void timerEvent();
    void gameStart();

private:
    Ui::Widget *ui;
    snake *player_snake;
    QPixmap *pix;
    QTimer *rotate_right_timer;
    QTimer *rotate_left_timer;
    QTimer *main_timer;
    QList<ball *> *ball_list;
    QPainterPath border;
    QPen border_style;
    QPushButton *game_start_button;
    int ball_count;
};
#endif // WIDGET_H
