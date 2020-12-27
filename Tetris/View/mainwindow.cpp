#include "View/mainwindow.h"
#include "View/optionsdialog.h"
#include "View/enddialog.h"

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QColorDialog>

MainWindow::MainWindow(GameArea &scene, NextBlock &nextblockscene, QWidget *parent):
    QMainWindow(parent),
    view_(this),
    nextBlockView_(this)
{
    setWindowTitle("Ebin Tetris Game");
    this->resize(460,520);
    this->setMinimumSize(400,500);

    // Setting background image
    QPixmap bkgnd("../Tetris/Images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    // View and scene for gamearea
    view_.setScene(&scene);
    scene_ = &scene;
    view_.setGeometry(20,20,240,480);
    view_.show();
    view_.setBackgroundBrush( QBrush(Qt::black, Qt::SolidPattern) );

    // View and scene for nextblock
    nextBlockView_.setScene(&nextblockscene);
    nextBlockScene_ = &nextblockscene;
    nextBlockView_.setGeometry(280, 20, 80, 80);
    nextBlockView_.show();
    nextblockscene.setBackgroundBrush( QBrush(Qt::black, Qt::SolidPattern) );

//    QTextBrowser* nextBlockText = new QTextBrowser(this);
//    nextBlockText->setText("Seuraava:");
//    nextBlockText->setGeometry(280, 20, 80, 30);

    timer_ = new QTimer(this);

    QWidget* wdg = new QWidget(this);

    // The buttons on the side of the mainwindow:
    QVBoxLayout* vlay = new QVBoxLayout(wdg);
    QPushButton* startBtn = new QPushButton("Aloita");
    vlay->addWidget(startBtn);
    QPushButton* stopBtn = new QPushButton("Tauko");
    vlay->addWidget(stopBtn);
    QPushButton* difficultyBtn = new QPushButton("Vaikeustaso");
    vlay->addWidget(difficultyBtn);
    QPushButton* quitBtn = new QPushButton("Lopeta");
    vlay->addWidget(quitBtn);
    wdg->setLayout(vlay);

    scene.addWidget(wdg);
    wdg->setGeometry(280,150,150,150);

    // Adding scoring scene to show players score
    QWidget* scoreWidget = new QWidget( this );
    QHBoxLayout* hlay = new QHBoxLayout(scoreWidget);
    QLabel* scoreText = new QLabel( this );
    hlay->addWidget(scoreText);
//    scoreText->setFrameStyle(QFrame::NoFrame);
    scoreText->setText ( "SCORE:" );

    scoreLabel_ = new QLabel( this );
    scoreLabel_->setNum(0);
    hlay->addWidget( scoreLabel_ );
    scoreWidget->setLayout( hlay );
    scene.addWidget( scoreWidget );
    scoreWidget->setGeometry(280,450,150,50);

    scoreLabel_->setStyleSheet("QLabel { background-color : black; color : white; }");
    scoreText->setStyleSheet("QLabel { background-color : black; color : white; }");
    scoreLabel_->setAlignment(Qt::AlignCenter);
//    QColor color(178,102,255);
//    QPalette palette2 = scoreText->palette();
//    palette2.setColor(QPalette::WindowText, color);
//    scoreText->setPalette(palette2);
//    scoreLabel_->setPalette(palette2);

    // Connecting signals and slots
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::pauseGame);
    connect(difficultyBtn, &QPushButton::clicked, this, &MainWindow::showOptionsDialog);
    connect(quitBtn, &QPushButton::clicked, this, &MainWindow::close);
    connect(this, &MainWindow::gameStarted, scene_, &GameArea::addTetromino);
    connect(timer_, &QTimer::timeout, scene_, &GameArea::tetrominoFall);
    connect(this, &MainWindow::togglePause, scene_, &GameArea::togglePauseSituation);
    connect(scene_, &GameArea::gameOver, this, &MainWindow::endGame);
    connect(scene_, &GameArea::pauseGame, this, &MainWindow::pauseGame);
    connect(scene_, &GameArea::displayScore, this, &MainWindow::showScore);
    connect(this, &MainWindow::changeDifficulty, scene_, &GameArea::setDifficulty);
}

void MainWindow::startGame()
{
    if ( not isRunning_ ) {
        timer_->start(interval_);
        isPaused_ = false;
        emit gameStarted();
        isRunning_ = true;
    }
}

void MainWindow::pauseGame()
{
    if ( isRunning_ ) {
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
}

void MainWindow::showOptionsDialog()
{
    if ( !isPaused_ ) {
        pauseGame();
    }
    OptionsDialog* dialog = new OptionsDialog(this);
//    dialog->setPalette(QPalette(QColor(100,0,100)));
    connect(dialog, &OptionsDialog::setDifficulty, this, &MainWindow::setDifficulty );
    dialog->exec();
    pauseGame();
}

void MainWindow::setDifficulty(int interval)
{
    interval_ = interval;
    timer_->setInterval(interval);
    qDebug() << "vaikeustaso on " << 4- (interval / 500);
    emit changeDifficulty( 4 - (interval / 500) );
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

void MainWindow::showScore(int scoreAmount)
{
    scoreLabel_->setNum( scoreAmount );
}


