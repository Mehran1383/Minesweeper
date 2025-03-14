#include "squarebuttongrid.h"
#include <qdebug.h>
SquareButtonGrid::SquareButtonGrid(QWidget *parent, QGridLayout* layout) : QWidget(parent)
{
    this->gridLayout = layout;
}

SquareButtonGrid::~SquareButtonGrid()
{
    delete [] buttonsMap;
}

void SquareButtonGrid::createMap(int row, int col)
{
    buttonsMap = new QPushButton**[row];
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col; j++)
            buttonsMap[i] = new QPushButton*[col];

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col; j++){
            buttonsMap[i][j] = new QPushButton;
            buttonsMap[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttonsMap[i][j]->setCursor(Qt::PointingHandCursor);
            gridLayout->addWidget(buttonsMap[i][j], i, j);
        }
    }
    gridLayout->setVerticalSpacing(2);
    gridLayout->setHorizontalSpacing(2);
}




