#include "gamelogic.h"

GameLogic::GameLogic(int Row, int Col, int numOfMins)
{
    int randomRow, randomCol;

    rowNum = Row;
    colNum = Col;

    mins = new bool*[rowNum];
    map = new int*[rowNum];

    for(int i = 0 ; i < rowNum ; i++)
        for(int j = 0 ; j < colNum; j++){
            mins[i] = new bool[colNum];
            map[i] = new int[colNum];
        }
    for(int i = 0 ; i < rowNum ; i++)
        for(int j = 0 ; j < colNum; j++){
            mins[i][j] = false;
            map[i][j] = -1;
        }
    while(numOfMins > 0){
        randomRow = QRandomGenerator::global()->bounded(0, rowNum);
        randomCol = QRandomGenerator::global()->bounded(0, colNum);
        if(mins[randomRow][randomCol] != true){
            mins[randomRow][randomCol] = true;
            numOfMins--;
        }
    }
}

GameLogic::~GameLogic()
{
    delete [] mins;
    delete [] map;
}

void GameLogic::buttonClicked(int row, int col)
{
//    for(int i = 0 ; i < row ; i++){
//        for(int j = 0 ; j < col ; j++){

//        }
//    }
    map[row][col] = 0;

    emit finished();
}

