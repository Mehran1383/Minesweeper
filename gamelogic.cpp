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
    while(numOfMins >= 0){
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
    if(mins[row][col]){
        minRow = row;
        minCol = col;
        emit userFailed();
        return;
    }


    for(int i = 0 ; i < rowNum ; i++){
        for(int j = 0 ; j < colNum ; j++){

        }
    }
    map[row][col] = 0;

    emit finished();
}

