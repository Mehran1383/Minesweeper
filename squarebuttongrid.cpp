#include "squarebuttongrid.h"
#include <qdebug.h>
SquareButtonGrid::SquareButtonGrid(QGridLayout* layout, QTimer* timer, int row, int col, int numOfMins)
{
    this->gridLayout = layout;
    this->timer = timer;

    logic = new GameLogic(row, col, numOfMins);
    logic->rowNum = row;
    logic->colNum = col;

    buttonsMap = new QPushButton**[row];
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col; j++)
            buttonsMap[i] = new QPushButton*[col];

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col; j++){
            buttonsMap[i][j] = new QPushButton;
            buttonsMap[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttonsMap[i][j]->setCursor(Qt::PointingHandCursor);
            buttonsMap[i][j]->setStyleSheet("border :1px solid gray; border-radius: 0px;");
            gridLayout->addWidget(buttonsMap[i][j], i, j);
            connect(buttonsMap[i][j], &QPushButton::clicked, [this, i, j](){
                this->logic->buttonClicked(i, j);
                this->startTimer();
            });
        }
    }
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);

    connect(logic, &GameLogic::userFailed, [this, timer](){
        this->showMins();
        timer->stop();
    });

    connect(logic, &GameLogic::finished,
            this, &SquareButtonGrid::updateMap);

}

SquareButtonGrid::~SquareButtonGrid()
{
    for(int i = 0 ; i < logic->rowNum ; i++)
        for(int j = 0 ; j < logic->colNum ; j++)
            delete buttonsMap[i][j];

    delete logic;
}

void SquareButtonGrid::startTimer()
{
    if(!timer->isActive()){
        timer->start();
        emit timerStarted();
    }
}

void SquareButtonGrid::updateMap()
{
    for(int i = 0 ; i < logic->rowNum ; i++){
        for(int j = 0 ; j < logic->colNum ; j++){
            if(logic->map[i][j] == -1){
                buttonsMap[i][j]->setDisabled(1);
                buttonsMap[i][j]->setStyleSheet("background-color:#60798B; border-radius: 0px; border :1px solid gray;");
            }
            else if(logic->map[i][j] > 0){
                buttonsMap[i][j]->setText(QString::fromStdString(std::to_string(logic->map[i][j])));
                switch (logic->map[i][j]) {
                case 1 :
                    buttonsMap[i][j]->setStyleSheet("color: lightblue; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 2:
                    buttonsMap[i][j]->setStyleSheet("color: darkgreen; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 3:
                    buttonsMap[i][j]->setStyleSheet("color: orange; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 4:
                    buttonsMap[i][j]->setStyleSheet("color: red; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 5:
                    buttonsMap[i][j]->setStyleSheet("color: darkred; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                }
                buttonsMap[i][j]->setDisabled(1);
            }
        }
    }
}

void SquareButtonGrid::showMins()
{
    int size;
    if(logic->rowNum <= 8)
        size = 30;
    else if(logic->rowNum > 8 && logic->rowNum <= 16)
        size = 20;
    else if(logic->rowNum > 16 && logic->rowNum <= 24)
        size = 15;
    else
        size = 10;

    for(int i = 0 ; i < logic->rowNum ; i++){
        for(int j = 0 ; j < logic->colNum; j++){
            if(logic->mins[i][j] == true){
                buttonsMap[i][j]->setIcon(QIcon(":/icons/logo.ico"));
                buttonsMap[i][j]->setIconSize(QSize(size,size));
            }
            buttonsMap[i][j]->setDisabled(1);
        }
    }
    buttonsMap[logic->minRow][logic->minCol]->setStyleSheet("background-color: darkred; border-radius: 0px;border :1px solid gray;");
}




