#include "gamelogic.h"
#include <QtDebug>
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
            map[i][j] = 0;
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

    map[row][col] = -1;
    checkNeighbors(row, col);

    if(row > 0 && col > 0)
        checkNeighbors(row-1, col-1);
    if(row > 0)
        checkNeighbors(row-1, col);
    if(row > 0 && col+1 < colNum)
        checkNeighbors(row-1, col+1);
    if(col > 0)
        checkNeighbors(row, col-1);
    if(col+1 < colNum)
        checkNeighbors(row, col+1);
    if(row+1 < rowNum && col > 0)
        checkNeighbors(row+1, col-1);
    if(row+1 < rowNum)
        checkNeighbors(row+1, col);
    if(row+1 < rowNum && col+1 < colNum)
        checkNeighbors(row+1, col+1);

    emit finished();
}

void GameLogic::checkNeighbors(int row, int col)
{
    if(map[row][col] == 0 && mins[row][col] == 0){

        // Left-Up
        if((row > 0 && col > 0) && mins[row-1][col-1])
            map[row][col]++;

        // Up
        if(row > 0 && mins[row-1][col])
            map[row][col]++;

        // Right-Up
        if((row > 0 && col+1 < colNum) && mins[row-1][col+1])
            map[row][col]++;

        // Left
        if(col > 0 && mins[row][col-1])
            map[row][col]++;

        // Right
        if(col+1 < colNum && mins[row][col+1])
            map[row][col]++;

        // Left-Down
        if((row+1 < rowNum && col > 0) && mins[row+1][col-1])
            map[row][col]++;

        // Down
        if(row+1 < rowNum  && mins[row+1][col])
            map[row][col]++;

        // Right-Down
        if((row+1 < rowNum && col+1 < colNum) && mins[row+1][col+1])
            map[row][col]++;

        if(map[row][col] > 0)
            return;

        map[row][col] = -1;

        if(row > 0 && col > 0)
            checkNeighbors(row-1, col-1);
        if(row > 0)
            checkNeighbors(row-1, col);
        if(row > 0 && col+1 < colNum)
            checkNeighbors(row-1, col+1);
        if(col > 0)
            checkNeighbors(row, col-1);
        if(col+1 < colNum)
            checkNeighbors(row, col+1);
        if(row+1 < rowNum && col > 0)
            checkNeighbors(row+1, col-1);
        if(row+1 < rowNum)
            checkNeighbors(row+1, col);
        if(row+1 < rowNum && col+1 < colNum)
            checkNeighbors(row+1, col+1);

    }
}

