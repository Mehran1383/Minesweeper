#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    ui->stackedWidget->setCurrentIndex(0);

    // Timer setup
    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(ui->mode1, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->mode2, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->mode3, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->customMode, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->changeDifficulty, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

}

MainWindow::~MainWindow()
{
    if(gameBoard != nullptr)
        delete gameBoard;

    delete ui;
}

void MainWindow::on_mode1_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, timer, 8, 8, 10);
    this->installEventFilter(gameBoard);
    connect(gameBoard, &GameBoard::timerStarted,
            this, &MainWindow::updatePauseButton);

}

void MainWindow::on_mode2_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, timer, 16, 16, 40);
    this->installEventFilter(gameBoard);
    connect(gameBoard, &GameBoard::timerStarted,
            this, &MainWindow::updatePauseButton);
}

void MainWindow::on_mode3_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, timer, 24, 24, 99);
    this->installEventFilter(gameBoard);
    connect(gameBoard, &GameBoard::timerStarted,
            this, &MainWindow::updatePauseButton);
}

void MainWindow::on_changeDifficulty_clicked()
{
    delete gameBoard;
    gameBoard = nullptr;

    timer->stop();
    ui->pause->setText("Pause");
}

void MainWindow::on_pause_clicked()
{
    if(timer->isActive()){
        timer->stop();
        ui->pause->setText("Resume");
    }else{
        timer->start();
        ui->pause->setText("Pause");
    }
}

void MainWindow::updatePauseButton()
{
    ui->pause->setText("Pause");
}


void MainWindow::animateTransition()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    int newIndex = (currentIndex + 1) % 2;

    QWidget *currentWidget = ui->stackedWidget->widget(currentIndex);
    QWidget *nextWidget = ui->stackedWidget->widget(newIndex);

    int width = ui->stackedWidget->width();
    int height = ui->stackedWidget->height();

    // Ensure the next widget is positioned to the right of the stacked widget
    nextWidget->setGeometry(width, 0, width, height);
    nextWidget->show(); // Make sure the next widget is visible

    // Animate the current widget to the left
    QPropertyAnimation *animationCurrent = new QPropertyAnimation(currentWidget, "geometry");
    animationCurrent->setDuration(500);
    animationCurrent->setStartValue(QRect(0, 0, width, height));

    if(newIndex == 1){
        animationCurrent->setEndValue(QRect(-width, 0, width, height));
    }else{
        animationCurrent->setEndValue(QRect(width, 0, width, height));
    }

    // Animate the next widget from the right
    QPropertyAnimation *animationNext = new QPropertyAnimation(nextWidget, "geometry");
    animationNext->setDuration(500);
    animationNext->setStartValue(QRect(width, 0, width, height));
    animationNext->setEndValue(QRect(0, 0, width, height));


    // Use a parallel animation group to run both animations simultaneously
    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;
    animationGroup->addAnimation(animationCurrent);
    animationGroup->addAnimation(animationNext);

    // Set the animation group as the parent of the animations
    animationCurrent->setParent(animationGroup);
    animationNext->setParent(animationGroup);

    // Set the current index of the stacked widget to the new index after the animation finishes
    QStackedWidget* stack = ui->stackedWidget;
    QObject::connect(animationGroup, &QParallelAnimationGroup::finished, [stack, newIndex, animationGroup]() {
        stack->setCurrentIndex(newIndex);
        animationGroup->deleteLater();
    });

    // Start the animation
    animationGroup->start();
}


