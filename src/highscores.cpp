#include "highscores.h"
#include "ui_highscores.h"

HighScores::HighScores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScores)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/icons/logo.ico"));

    QHeaderView *headerView;
    headerView = ui->table1->horizontalHeader();
    headerView->setStretchLastSection(1);
    headerView = ui->table2->horizontalHeader();
    headerView->setStretchLastSection(1);
    headerView = ui->table3->horizontalHeader();
    headerView->setStretchLastSection(1);
}

HighScores::~HighScores()
{
    delete ui;
}

QTableView* HighScores::table(int mode)
{
    switch (mode) {
    case 1: return ui->table1;
    case 2: return ui->table2;
    case 3: return ui->table3;
    }
}

