#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    ui->stackedWidget->setCurrentIndex(0);

    // Timer setup
    timer.setInterval(1000);

    // Set time
    sec = min = 0;
    showTime();

    this->gameBoard = nullptr;

    // Database Setup
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("Minesweeper.db");
    dbManager = new DatabaseManager(dbPath);

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

    connect(&timer, &QTimer::timeout,
            this, &MainWindow::showTime);

    connect(ui->actionScores, &QAction::triggered,
            this, &MainWindow::showStats);

}

MainWindow::~MainWindow()
{
    if(gameBoard != nullptr)
        delete gameBoard;

    delete ui;
}

void MainWindow::init()
{
    this->installEventFilter(gameBoard);
    connect(gameBoard, &GameBoard::timerStarted,
            this, &MainWindow::updatePauseButton);
    connect(gameBoard, &GameBoard::flagChanged,
            this, &MainWindow::changeFlagCounter);
    connect(gameBoard, &GameBoard::userWon,
            this, &MainWindow::checkScore);
    changeFlagCounter();
}

void MainWindow::on_mode1_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode1Dim, mode1Dim, mode1Mines);
    init();
}

void MainWindow::on_mode2_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode2Dim, mode2Dim, mode2Mines);
    init();
}

void MainWindow::on_mode3_clicked()
{
    gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode3Dim, mode3Dim, mode3Mines);
    init();
}

void MainWindow::on_changeDifficulty_clicked()
{
    delete gameBoard;
    gameBoard = nullptr;

    timer.stop();
    sec = min = 0;
    showTime();
    ui->pause->setText("Pause");
}

void MainWindow::on_pause_clicked()
{
    if(timer.isActive()){
        timer.stop();
        ui->pause->setText("Resume");
    }else{
        timer.start();
        ui->pause->setText("Pause");
    }
}

void MainWindow::on_startOver_clicked()
{
    int mode = gameBoard->getMode();
    delete gameBoard;

    switch (mode) {
    case 1: gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode1Dim, mode1Dim, mode1Mines); break;
    case 2: gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode2Dim, mode2Dim, mode2Mines); break;
    case 3: gameBoard = new GameBoard(this, ui->mapLayout, &timer, mode3Dim, mode3Dim, mode3Mines); break;
    //case 4: gameBoard = new GameBoard(this, ui->mapLayout, timer, 24, 24, 99);
    }

    init();
    timer.stop();
    sec = min = 0;
    showTime();
}

void MainWindow::updatePauseButton()
{
    ui->pause->setText("Pause");
}

void MainWindow::showStats()
{

}

bool MainWindow::checkScore()
{

}

void MainWindow::showTime()
{
    time.setHMS(0,min,sec);
    QString text = time.toString("mm:ss");
    ui->lcdNumber->display(text);

    sec++;
    if(sec == 60){
        sec = 0;
        min++;
    }
}

void MainWindow::changeFlagCounter()
{
    int total;
    int remainded = gameBoard->getFlags();
    int mode = gameBoard->getMode();

    switch (mode) {
    case 1: total = mode1Mines; break;
    case 2: total = mode2Mines; break;
    case 3: total = mode3Mines; break;
    //case 4:
    }

    ui->label->setText("      " + QString::fromStdString(std::to_string(remainded) + "/" + std::to_string(total)));
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




