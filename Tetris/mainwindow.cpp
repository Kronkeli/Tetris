#include "mainwindow.h"
#include "optionsdialog.h"
#include "enddialog.h"

#include <QDialog>
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
    this->resize(460,520);
    this->setMinimumSize(400,500);

    // View and scene for gamearea
    view_.setScene(&scene);
    scene_ = &scene;
    view_.setGeometry(20,20,240,480);
    view_.show();

    // View and scene for nextblock
    nextBlockView_.setScene(&nextblockscene);
    nextBlockScene_ = &nextblockscene;
    nextBlockView_.setGeometry(280, 20, 80, 80);
    nextBlockView_.show();

//    QTextBrowser* nextBlockText = new QTextBrowser(this);
//    nextBlockText->setText("Seuraava:");
//    nextBlockText->setGeometry(280, 20, 80, 30);

    timer_ = new QTimer(this);

    // Start button:
    QPushButton* start_button = new QPushButton("Start");
    qDebug() << start_button->pos();

    QWidget * wdg = new QWidget(this);

    QVBoxLayout *vlay = new QVBoxLayout(wdg);
    QPushButton *btn1 = new QPushButton("Aloita");
    vlay->addWidget(btn1);
    QPushButton *btn2 = new QPushButton("Tauko");
    vlay->addWidget(btn2);
    QPushButton *btn3 = new QPushButton("Vaikeustaso");
    vlay->addWidget(btn3);
    QPushButton *btn4 = new QPushButton("Lopeta");
    vlay->addWidget(btn4);
    wdg->setLayout(vlay);

    scene.addWidget(wdg);
    wdg->setGeometry(280,150,150,150);

    // Connecting signals
    connect(btn1, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::pauseGame);
    connect(btn3, &QPushButton::clicked, this, &MainWindow::showOptionsDialog);
    connect(btn4, &QPushButton::clicked, this, &MainWindow::close);
    connect(this, &MainWindow::gameStarted, scene_, &GameArea::addTetromino);
    connect(timer_, &QTimer::timeout, scene_, &GameArea::tetrominoFall);
    connect(this, &MainWindow::togglePause, scene_, &GameArea::togglePauseSituation);
    connect(scene_, &GameArea::gameOver, this, &MainWindow::endGame);
}

void MainWindow::startGame()
{
    timer_->start(interval_);
    isPaused_ = false;
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

void MainWindow::showOptionsDialog()
{
    if ( !isPaused_ ) {
        pauseGame();
    }
    OptionsDialog* dialog = new OptionsDialog(this);
    connect(dialog, &OptionsDialog::setDifficulty, this, &MainWindow::setDifficulty );
    dialog->exec();
    pauseGame();
}

void MainWindow::setDifficulty(int interval)
{
    qDebug() << "caihdetaan diffclty: " << interval;
    interval_ = interval;
    timer_->setInterval(interval);
}

void MainWindow::endGame()
{
    if ( !isPaused_ ) {
        pauseGame();
    }
    EndDialog* dialog = new EndDialog(this);
    connect(dialog, &EndDialog::quitOrRestart, this, &MainWindow::gameOver);
    connect(dialog, &EndDialog::clearData, scene_, &GameArea::restartScene);
    dialog->exec();
}

void MainWindow::gameOver(bool playAgain)
{
    if ( playAgain ) {
        showOptionsDialog();
    }
    else {
        close();
    }
}


