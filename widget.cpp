#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    gameStart();
}

void Widget::gameStart()
{
    pix = new QPixmap(ui->paintArea->size());
    player_snake = new snake;
    player_snake->init(ui->paintArea->width(), ui->paintArea->height());
    ui->paintArea->init();
    connect(player_snake, SIGNAL(hitBorder()), this, SLOT(gameOver()));
    connect(player_snake, SIGNAL(hitBody()), this, SLOT(gameOver()));
    ball_count = 5; //未来更新难度选项或者实时调整球的数量
    ball_list = new QList<ball *>;
    for (int i = 0; i < ball_count; i++)
    {
        ball *temp_ball = new ball(ui->paintArea->width(), ui->paintArea->height());
        ball_list->append(temp_ball);
    }

    QTimer *main_timer = new QTimer;
    main_timer->start(3);
    connect(main_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

void Widget::gameOver()
{
    exit(0);
}

void Widget::timerEvent()
{
    pix->fill(Qt::white);
    player_snake->snakeMove();
    ui->paintArea->drawPix(pix, player_snake->getPath(), player_snake->getStyle());
    while (ball_list->count() < ball_count)
    {
        ball *temp_ball = new ball(ui->paintArea->width(), ui->paintArea->height());
        ball_list->append(temp_ball);
    }
    QList<ball *>::iterator i = ball_list->begin();
    for (; i != ball_list->end();)
    {
        if (((*i)->getPos().x() - player_snake->getEndPos().x()) * ((*i)->getPos().x() - player_snake->getEndPos().x()) + ((*i)->getPos().y() - player_snake->getEndPos().y()) * ((*i)->getPos().y() - player_snake->getEndPos().y()) <= 100)
        {
            player_snake->eatBall();
            ball_list->erase(i);
        }
        else
        {
            ui->paintArea->drawBall(pix, (*i)->getPos(), (*i)->getStyle());
            i++;
        }
    }

    ui->paintArea->paint(pix);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Right)
    {
        rotate_right_timer = new QTimer;
        rotate_right_timer->start(1);
        connect(rotate_right_timer, SIGNAL(timeout()), player_snake, SLOT(rotateRight()));
    }
    if (e->key() == Qt::Key_Left)
    {
        rotate_left_timer = new QTimer;
        rotate_left_timer->start(1);
        connect(rotate_left_timer, SIGNAL(timeout()), player_snake, SLOT(rotateLeft()));
    }
}

void Widget::keyReleaseEvent(QKeyEvent *e)
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

Widget::~Widget()
{
    delete ui;
}
