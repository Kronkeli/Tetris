#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QKeyEvent>

MainWindow::MainWindow(GameArea &scene, QWidget *parent):
    QMainWindow(parent),
    view_(this)
{
    setWindowTitle("Ebin Tetris Game");
    view_.setScene(&scene);
    scene_ = &scene;

    this->resize(1000,1000);
    // Constructing the graphicsview for the tetrominos
    view_.setGeometry(40,40,240,480);

    view_.show();

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
    wdg->setGeometry(600,150,150,300);

    // Connecting signals
    connect(btn1, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(this, &MainWindow::gameStarted, scene_, &GameArea::addTetromino);
    connect(timer_, &QTimer::timeout, scene_, &GameArea::tetrominoFall);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::pauseGame);
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
}


