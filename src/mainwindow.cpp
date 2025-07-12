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
    ui->pause->setDisabled(1);

    // Timer setup
    timer.setInterval(1000);

    // Set time
    sec = min = 0;
    showTime();

    this->gameBoard = nullptr;
    this->mapLayout = nullptr;
    this->view1 = highScoresTables.table(1);
    this->view2 = highScoresTables.table(2);
    this->view3 = highScoresTables.table(3);

    // Database setup
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("Minesweeper.db");

    dbManager = new DatabaseManager(dbPath);

    connect(ui->mode1, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->mode2, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->mode3, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(ui->changeDifficulty, &QPushButton::clicked,
            this, &MainWindow::animateTransition);

    connect(&timer, &QTimer::timeout,
            this, &MainWindow::showTime);

    connect(ui->actionScores, &QAction::triggered,
            this, &MainWindow::showTables);

    connect(&customMode, &CustomMode::accepted,[this](){
        this->createCustomGame();
        this->animateTransition();
    });
}

MainWindow::~MainWindow()
{
    if(gameBoard != nullptr)
        delete gameBoard;

    if(mapLayout != nullptr)
        delete mapLayout;

    delete ui;
}

void MainWindow::init()
{
    this->installEventFilter(gameBoard);
    connect(gameBoard, &GameBoard::timerStarted,
            this, &MainWindow::updatePauseButton);
    connect(gameBoard, &GameBoard::flagChanged, [this](){
        this->changeFlagCounter();
        ui->pause->setDisabled(0);
    });
    connect(gameBoard, &GameBoard::userWon,
            this, &MainWindow::updatetTable);
    connect(gameBoard, &GameBoard::gameOver, [this](){
        ui->pause->setDisabled(1);
    });
    connect(gameBoard, &GameBoard::windowResized, [this](){
        if(timer.isActive()){
            timer.stop();
            ui->pause->setText("Resume");
        }
    });
    changeFlagCounter();
}

void MainWindow::on_mode1_clicked()
{
    mapLayout = new QGridLayout;
    ui->layout->addLayout(mapLayout, 0, 0);
    gameBoard = new GameBoard(this, mapLayout, &timer, mode1Dim, mode1Dim, mode1Mines);
    init();
    this->setMinimumSize(520, 340);
}


void MainWindow::on_mode2_clicked()
{
    mapLayout = new QGridLayout;
    ui->layout->addLayout(mapLayout, 0, 0);
    gameBoard = new GameBoard(this, mapLayout, &timer, mode2Dim, mode2Dim, mode2Mines);
    init();
    this->setMinimumSize(550, 370);
}

void MainWindow::on_mode3_clicked()
{
    mapLayout = new QGridLayout;
    ui->layout->addLayout(mapLayout, 0, 0);
    gameBoard = new GameBoard(this, mapLayout, &timer, mode3Dim, mode3Dim, mode3Mines);
    init();
    this->setMinimumSize(640, 460);
}

void MainWindow::on_customMode_clicked()
{
    customMode.show();
}

void MainWindow::createCustomGame()
{
    mapLayout = new QGridLayout;
    ui->layout->addLayout(mapLayout, 0, 0);
    gameBoard = new GameBoard(this, mapLayout, &timer, customMode.getRow(), customMode.getCol(), customMode.getMine());
    init();
    this->setMinimumSize(640, 460);
}

void MainWindow::on_changeDifficulty_clicked()
{
    delete gameBoard;
    delete mapLayout;
    gameBoard = nullptr;
    mapLayout = nullptr;

    timer.stop();
    sec = min = 0;
    showTime();
    ui->pause->setText("Pause");
    this->setMinimumSize(400, 300);
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
    delete mapLayout;
    gameBoard = nullptr;
    mapLayout = nullptr;

    switch (mode) {
    case 1: on_mode1_clicked(); break;
    case 2: on_mode2_clicked(); break;
    case 3: on_mode3_clicked(); break;
    case 4: createCustomGame();
    }

    timer.stop();
    sec = min = 0;
    showTime();

    ui->pause->setText("Pause");
    ui->pause->setDisabled(1);
}

void MainWindow::updatePauseButton()
{
    ui->pause->setDisabled(0);
    ui->pause->setText("Pause");
}

void MainWindow::showTables()
{
    dbManager->populateTable(view1, 1);
    dbManager->populateTable(view2, 2);
    dbManager->populateTable(view3, 3);
    highScoresTables.show();
}

void MainWindow::updatetTable()
{
    int mode = gameBoard->getMode();

    if(mode == 4)
        return;

    int score = min * 60 + sec - 1;

    if(dbManager->count(mode) >= MAX_RANK){
        if(score <= dbManager->maxScore(mode))
            dbManager->deleteUserRecord(mode);
        else
            return;
    }

    auto name = QInputDialog::getText(this, tr("Congratulations!"), tr("You've earned a good score!<br>Please enter your name:"));

    if(dbManager->updateUser(name, mode, score) == USER_NOT_FOUND)
        dbManager->addUser(name, mode, score);
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
    case 4: total = customMode.getMine();
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

    nextWidget->setGeometry(width, 0, width, height);
    nextWidget->show();

    QPropertyAnimation *animationCurrent = new QPropertyAnimation(currentWidget, "geometry");
    animationCurrent->setDuration(500);
    animationCurrent->setStartValue(QRect(0, 0, width, height));

    if(newIndex == 1){
        animationCurrent->setEndValue(QRect(-width, 0, width, height));
    }else{
        animationCurrent->setEndValue(QRect(width, 0, width, height));
    }

    QPropertyAnimation *animationNext = new QPropertyAnimation(nextWidget, "geometry");
    animationNext->setDuration(500);
    animationNext->setStartValue(QRect(width, 0, width, height));
    animationNext->setEndValue(QRect(0, 0, width, height));

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;
    animationGroup->addAnimation(animationCurrent);
    animationGroup->addAnimation(animationNext);

    animationCurrent->setParent(animationGroup);
    animationNext->setParent(animationGroup);

    QStackedWidget* stack = ui->stackedWidget;
    QObject::connect(animationGroup, &QParallelAnimationGroup::finished, [stack, newIndex, animationGroup]() {
        stack->setCurrentIndex(newIndex);
        animationGroup->deleteLater();
    });

    animationGroup->start();
}




