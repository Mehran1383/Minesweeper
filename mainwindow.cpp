#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/assets/logo.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

