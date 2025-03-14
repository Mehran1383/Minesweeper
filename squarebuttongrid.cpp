#include "squarebuttongrid.h"
#include <qdebug.h>
SquareButtonGrid::SquareButtonGrid(QGridLayout* layout, int row, int col, int numOfMins)
{
    this->gridLayout = layout;

    logic = new GameLogic(row, col, numOfMins);
    logic->rowNum = row;
    logic->colNum = col;
    connect(logic, &GameLogic::finished,
            this, &SquareButtonGrid::updateMap);

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
            connect(buttonsMap[i][j], &QPushButton::clicked,
                    [this, i, j](){this->logic->buttonClicked(i, j);});
        }
    }
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);
}

SquareButtonGrid::~SquareButtonGrid()
{
    for(int i = 0 ; i < logic->rowNum ; i++)
        for(int j = 0 ; j < logic->colNum ; j++)
            delete buttonsMap[i][j];

    delete logic;
}

void SquareButtonGrid::updateMap()
{
    for(int i = 0 ; i < logic->rowNum ; i++){
        for(int j = 0 ; j < logic->colNum ; j++){
            if(logic->map[i][j] == 0){
                buttonsMap[i][j]->setDisabled(1);
                buttonsMap[i][j]->setStyleSheet("background-color:#60798B; border-radius: 0px;");
            }
        }
    }
}




