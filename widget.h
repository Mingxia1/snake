#ifndef WIDGET_H
#define WIDGET_H

#include "ball.h"
#include "snake.h"
#include <QBitmap>
#include <QComboBox>
#include <QFont>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

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
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
    void drawBall(QPointF, const QPen &);
    void drawSnake();
    void paintEvent(QPaintEvent *) override;
    void updateScore();
    inline void clearScreen();

  public slots:
    void gameOver();
    void timerEvent();
    void gameStart();
    void mainMenu();
    void settingMenu();

  private:
    Ui::Widget *ui;
    snake *player_snake;
    QPixmap *pix, *top_banner, *menu_pix;
    QLabel *game_over_menu, *main_menu, *setting_menu;
    QComboBox *difficulty_select;
    QTimer *rotate_right_timer;
    QTimer *rotate_left_timer;
    QTimer *main_timer;
    QList<ball *> *ball_list;
    QPainterPath border;
    QPen border_style;
    QRect *score_box, *game_over_box, *game_over_score_text_box, *game_over_score_box;
    QFont score_font, game_over_font;
    int ball_count, score;
};
#endif // WIDGET_H
