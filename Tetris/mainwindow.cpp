#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QKeyEvent>

MainWindow::MainWindow(GameArea &scene, NextBlock &nextblockscene, QWidget *parent):
    QMainWindow(parent),
    view_(this),
    nextBlockView_(this)
{
    setWindowTitle("Ebin Tetris Game");
    this->resize(500,600);

    // View and scene for gamearea
    view_.setScene(&scene);
    scene_ = &scene;
    view_.setGeometry(40,40,240,480);
    view_.show();

    // View and scene for nextblock
    nextBlockView_.setScene(&nextblockscene);
    nextBlockScene_ = &nextblockscene;
    nextBlockView_.setGeometry(300, 60, 80, 80);
    nextBlockView_.show();

    QTextBrowser* nextBlockText = new QTextBrowser(this);
    nextBlockText->setText("Seuraava:");
    nextBlockText->setGeometry(300, 40, 80, 20);

    timer_ = new QTimer(this);

    // Start button:
    QPushButton* start_button = new QPushButton("Start");
    qDebug() << start_button->pos();

    QWidget * wdg = new QWidget(this);

    QVBoxLayout *vlay = new QVBoxLayout(wdg);
    QPushButton *btn1 = new QPushButton("Start");
    vlay->addWidget(btn1);
    QPushButton *btn2 = new QPushButton("Pause");
    vlay->addWidget(btn2);
    QPushButton *btn3 = new QPushButton("Exit");
    vlay->addWidget(btn3);
    wdg->setLayout(vlay);

    scene.addWidget(wdg);
    wdg->setGeometry(300,150,150,150);

    // Connecting signals
    connect(btn1, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::pauseGame);
    connect(btn3, &QPushButton::clicked, this, &MainWindow::close);
    connect(this, &MainWindow::gameStarted, scene_, &GameArea::addTetromino);
    connect(timer_, &QTimer::timeout, scene_, &GameArea::tetrominoFall);
    connect(this, &MainWindow::togglePause, scene_, &GameArea::togglePauseSituation);
}

void MainWindow::startGame()
{
    timer_->start(interval_);
    emit gameStarted();
}

void MainWindow::pauseGame()
{
    if ( !isPaused_) {
        timer_->stop();
        isPaused_ = true;
    }
    else {
        timer_->start(interval_);
        isPaused_ = false;
    }
    emit togglePause(isPaused_);
}


