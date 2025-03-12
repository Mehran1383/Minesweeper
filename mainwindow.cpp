#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
void animateTransition(QStackedWidget *stackedWidget, int newIndex);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/assets/logo.ico"));
    ui->stackedWidget->setCurrentIndex(0);

    QStackedWidget *stackWidget = ui->stackedWidget;

    connect(ui->mode1, &QPushButton::clicked, [stackWidget]() {
        animateTransition(stackWidget, 1);
    });

    connect(ui->mode2, &QPushButton::clicked, [stackWidget]() {
        animateTransition(stackWidget, 1);
    });

    connect(ui->mode3, &QPushButton::clicked, [stackWidget]() {
        animateTransition(stackWidget, 1);
    });

    connect(ui->customMode, &QPushButton::clicked, [stackWidget]() {
        animateTransition(stackWidget, 1);
    });

    connect(ui->changeDifficulty, &QPushButton::clicked, [stackWidget]() {
        animateTransition(stackWidget, 0);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to animate the transition
void animateTransition(QStackedWidget *stackedWidget, int newIndex)
{
    int currentIndex = stackedWidget->currentIndex();
    if (currentIndex == newIndex) return;

    QWidget *currentWidget = stackedWidget->widget(currentIndex);
    QWidget *nextWidget = stackedWidget->widget(newIndex);

    int width = stackedWidget->width();
    int height = stackedWidget->height();

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
    QObject::connect(animationGroup, &QParallelAnimationGroup::finished, [stackedWidget, newIndex, animationGroup]() {
        stackedWidget->setCurrentIndex(newIndex);
        animationGroup->deleteLater();
    });

    // Start the animation
    animationGroup->start();
}

void MainWindow::createMap(int row, int col)
{
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col; j++){
            Map1[i][j] = new QPushButton;
            Map1[i][j]->setMinimumSize(25, 25);
            ui->buttonsLayout->addWidget(Map1[i][j], i, j);
        }
    }
    ui->buttonsLayout->setVerticalSpacing(0);
    ui->buttonsLayout->setHorizontalSpacing(1);
}

void MainWindow::on_mode1_clicked()
{
    createMap(8, 8);
}

void MainWindow::on_mode2_clicked()
{
    //createMap(16, 16);
}

void MainWindow::on_mode3_clicked()
{
    //createMap(30, 16);
}



void MainWindow::on_changeDifficulty_clicked()
{

}
