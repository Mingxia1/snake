#include "widget.h"
#include "./ui_widget.h"
#include "paintarea.h"
#include "snake.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    snake *playerSnake = new snake;
    playerSnake->init(ui->paintArea->width() / 2, ui->paintArea->height() / 2);
    ui->paintArea->init(playerSnake);
    connect(playerSnake, SIGNAL(hitBorder()), this, SLOT(gameOver()));
    connect(playerSnake, SIGNAL(hitBody()), this, SLOT(gameOver()));
    gameStart();
}

void Widget::gameStart()
{
    QTimer *draw_timer = new QTimer;
    draw_timer = new QTimer;
    draw_timer->start(2);
    // connect(ui->paintArea, SIGNAL(hitBorder()), this, SLOT(gameOver()));
    connect(draw_timer, SIGNAL(timeout()), ui->paintArea, SLOT(moveEvent()));
}

void Widget::gameOver()
{
    exit(0);
}

Widget::~Widget()
{
    delete ui;
}
