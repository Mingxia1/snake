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
    ball_count = 5;
    ball_list = new QList<ball *>;
    for (int i = 0; i < ball_count; i++)
    {
        ball *temp_ball = new ball(ui->paintArea->width(), ui->paintArea->height());
        ball_list->append(temp_ball);
    }

    QTimer *main_timer = new QTimer;
    main_timer->start(2);
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
