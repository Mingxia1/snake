#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    //为了符合静态代码检查规则的空初始化
    player_snake = nullptr;
    rotate_left_timer = nullptr;
    rotate_right_timer = nullptr;
    main_timer = nullptr;
    ball_list = nullptr;
    ball_count = 0;
    score = 0;
    //初始化画笔
    border_style.setWidth(20);
    border_style.setColor(Qt::black);
    border_style.setStyle(Qt::SolidLine);
    score_font.setPixelSize(50);
    game_over_font.setPixelSize(50);
    //初始化绘图画布
    pix = new QPixmap(800, 600);
    top_banner = new QPixmap(800, 50);
    menu_pix = new QPixmap(800, 650);
    pix->fill();
    top_banner->fill();
    menu_pix->fill();
    //初始化开始菜单label
    main_menu = new QLabel(this);
    main_menu->setGeometry(0, 0, 800, 650);
    main_menu->hide();
    //初始化开始菜单按钮
    auto *game_start_button = new QPushButton("开始", main_menu);
    game_start_button->setGeometry(main_menu->width() / 2 - 50, main_menu->height() / 2, 100, 50);
    connect(game_start_button, SIGNAL(clicked()), this, SLOT(gameStart()));
    auto *setting_button = new QPushButton("设置", main_menu);
    setting_button->setGeometry(main_menu->width() / 2 - 50, main_menu->height() / 2 + 60, 100, 50);
    connect(setting_button, SIGNAL(clicked()), this, SLOT(settingMenu()));
    //初始化设置label
    setting_menu = new QLabel(this);
    setting_menu->setGeometry(0, 0, 800, 650);
    setting_menu->hide();
    //初始化设置菜单组件
    difficulty_select = new QComboBox(setting_menu);
    difficulty_select->addItem("easy");
    difficulty_select->addItem("normal");
    difficulty_select->addItem("hard");
    difficulty_select->addItem("???");
    difficulty_select->setGeometry(setting_menu->width() / 2 - 50, setting_menu->height(), 100, 50);
    auto *setting_back_button = new QPushButton("返回", setting_menu);
    setting_back_button->setGeometry(setting_menu->width() / 2 - 50, setting_menu->height() / 2 + 60, 100, 50);
    connect(setting_back_button, SIGNAL(clicked()), this, SLOT(mainMenu()));
    //初始化游戏结束菜单label
    game_over_menu = new QLabel(this);
    game_over_menu->setGeometry(0, 0, 800, 650);
    game_over_menu->hide();
    auto *restart_button = new QPushButton("restart", game_over_menu);
    restart_button->setGeometry(pix->width() / 2 - 50, pix->height() / 2, 100, 50);
    connect(restart_button, SIGNAL(clicked()), this, SLOT(gameStart()));
    auto *main_menu_button = new QPushButton("主菜单", game_over_menu);
    main_menu_button->setGeometry(pix->width() / 2 - 50, pix->height() / 2 + 55, 100, 50);
    connect(main_menu_button, SIGNAL(clicked()), this, SLOT(mainMenu()));
    //其他初始化
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(800, 650);
    //初始化组件容器
    score_box = new QRect(375, 0, 50, 50);
    game_over_box = new QRect(200, 100, 400, 100);
    game_over_score_text_box = new QRect(230, 200, 300, 100);
    game_over_score_box = new QRect(500, 200, 100, 100);
    mainMenu();
}

inline void Widget::clearScreen()
{
    QList<QLabel *> list = this->findChildren<QLabel *>();
    foreach (auto i, list)
    {
        i->hide();
    }
}

void Widget::mainMenu()
{
    menu_pix->fill();
    main_menu->setPixmap(*menu_pix);
    clearScreen();
    main_menu->show();
}

void Widget::settingMenu()
{
    menu_pix->fill();
    setting_menu->setPixmap(*menu_pix);
    clearScreen();
    setting_menu->show();
}

void Widget::gameStart()
{
    clearScreen();
    player_snake = new snake;
    player_snake->init(pix->width(), pix->height());
    border.addRect(pix->rect());
    connect(player_snake, SIGNAL(hitBorder()), this, SLOT(gameOver()));
    connect(player_snake, SIGNAL(hitBody()), this, SLOT(gameOver()));
    score = 0;
    updateScore();
    ball_count = 5; //未来更新难度选项或者实时调整球的数量
    ball_list = new QList<ball *>;
    for (int i = 0; i < ball_count; i++)
    {
        ball *temp_ball = new ball(800, 600);
        ball_list->append(temp_ball);
    }
    main_timer = new QTimer;
    main_timer->start(3);
    connect(main_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

void Widget::gameOver()
{
    main_timer->stop();
    main_timer->~QTimer();
    menu_pix->fill();
    auto *p = new QPainter;
    p->begin(menu_pix);
    p->setFont(game_over_font);
    p->drawText(*game_over_box, Qt::AlignCenter, "Game Over");
    p->drawText(*game_over_score_text_box, Qt::AlignCenter, "Your Score:");
    QString tempString = QString::number(score);
    p->drawText(*game_over_score_box, Qt::AlignCenter, tempString);
    p->end();
    game_over_menu->setPixmap(*menu_pix);
    game_over_menu->show();
}

void Widget::timerEvent()
{
    pix->fill(Qt::white);
    player_snake->snakeMove();
    drawSnake();
    while (ball_list->count() < ball_count)
    {
        ball *temp_ball = new ball(800, 600);
        ball_list->append(temp_ball);
    }

    QList<ball *>::iterator i = ball_list->begin();
    for (; i != ball_list->end();)
    {
        if (((*i)->getPos().x() - player_snake->getEndPos().x()) *
                    ((*i)->getPos().x() - player_snake->getEndPos().x()) +
                ((*i)->getPos().y() - player_snake->getEndPos().y()) *
                    ((*i)->getPos().y() - player_snake->getEndPos().y()) <=
            100)
        {
            player_snake->eatBall();
            i = ball_list->erase(i);
            score++;
        }
        else
        {
            drawBall((*i)->getPos(), (*i)->getStyle());
            i++;
        }
    }
    updateScore();
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

void Widget::drawBall(QPointF pos, const QPen &pen)
{
    auto *p = new QPainter;
    p->begin(pix);
    p->setPen(pen);
    p->drawPoint(pos);
    p->end();
}

void Widget::drawSnake()
{
    auto *p = new QPainter;
    p->begin(pix);
    p->setPen(border_style);
    p->drawPath(border);
    p->setPen(player_snake->getStyle());
    p->drawPath(*(player_snake->getPath()));
    p->end();
}

void Widget::updateScore()
{
    top_banner->fill();
    auto *p = new QPainter;
    QString s = QString::number(score);
    p->begin(top_banner);
    p->setFont(score_font);
    p->drawText(*score_box, Qt::AlignCenter, s);
    p->end();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 50), *pix);
    painter.drawPixmap(QPoint(0, 0), *top_banner);
}

Widget::~Widget()
{
    delete ui;
}