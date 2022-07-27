#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化边界画笔
    border_style.setWidth(20);
    border_style.setColor(Qt::black);
    border_style.setStyle(Qt::SolidLine);
    //初始化按钮
    game_start_button = new QPushButton("开始", this);
    game_start_button->setGeometry(width() / 2, height() / 2, 100, 50);
    connect(game_start_button, SIGNAL(clicked()), this, SLOT(gameStart()));
    //初始化绘图画布
    pix = new QPixmap(size());
    pix->fill();
    setFocusPolicy(Qt::StrongFocus);
    mainMenu();
}

void Widget::mainMenu()
{
    game_start_button->show();
}

void Widget::gameStart()
{
    game_start_button->hide();
    player_snake = new snake;
    player_snake->init(width(), height());
    border.addRect(rect());
    connect(player_snake, SIGNAL(hitBorder()), this, SLOT(gameOver()));
    connect(player_snake, SIGNAL(hitBody()), this, SLOT(gameOver()));
    ball_count = 5; //未来更新难度选项或者实时调整球的数量
    ball_list = new QList<ball *>;
    for (int i = 0; i < ball_count; i++)
    {
        ball *temp_ball = new ball(width(), height());
        ball_list->append(temp_ball);
    }
    main_timer = new QTimer;
    main_timer->start(3);
    connect(main_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

void Widget::gameOver()
{
    main_timer->~QTimer();
    mainMenu();
}

void Widget::timerEvent()
{
    pix->fill(Qt::white);
    player_snake->snakeMove();
    drawSnake();
    while (ball_list->count() < ball_count)
    {
        ball *temp_ball = new ball(width(), height());
        ball_list->append(temp_ball);
    }
    QList<ball *>::iterator i = ball_list->begin();
    for (; i != ball_list->end();)
    {
        if (((*i)->getPos().x() - player_snake->getEndPos().x()) * ((*i)->getPos().x() - player_snake->getEndPos().x()) + ((*i)->getPos().y() - player_snake->getEndPos().y()) * ((*i)->getPos().y() - player_snake->getEndPos().y()) <= 100)
        {
            player_snake->eatBall();
            i = ball_list->erase(i);
        }
        else
        {
            drawBall((*i)->getPos(), (*i)->getStyle());
            i++;
        }
    }
    update();
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

void Widget::drawBall(QPointF pos, QPen pen)
{
    QPainter *p = new QPainter;
    p->begin(pix);
    p->setPen(pen);
    p->drawPoint(pos);
    p->end();
}

void Widget::drawSnake()
{
    QPainter *p = new QPainter;
    p->begin(pix);
    p->setPen(border_style);
    p->drawPath(border);
    p->setPen(player_snake->getStyle());
    p->drawPath(*(player_snake->getPath()));
    p->end();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
}

Widget::~Widget()
{
    delete ui;
}