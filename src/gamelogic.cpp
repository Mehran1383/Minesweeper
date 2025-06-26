#include "gamelogic.h"

GameLogic::GameLogic(int Row, int Col, int numOfMines)
{
    this->gameIsFinished = false;
    int randomRow, randomCol;

    rowNum = Row;
    colNum = Col;

    mines = new bool*[rowNum];
    map = new int*[rowNum];

    for(int i = 0 ; i < rowNum ; i++)
        for(int j = 0 ; j < colNum; j++){
            mines[i] = new bool[colNum];
            map[i] = new int[colNum];
        }
    for(int i = 0 ; i < rowNum ; i++)
        for(int j = 0 ; j < colNum; j++){
            mines[i][j] = false;
            map[i][j] = 0;
        }
    while(numOfMines >= 0){
        randomRow = QRandomGenerator::global()->bounded(0, rowNum);
        randomCol = QRandomGenerator::global()->bounded(0, colNum);
        if(mines[randomRow][randomCol] != true){
            mines[randomRow][randomCol] = true;
            numOfMines--;
        }
    }
}

GameLogic::~GameLogic()
{
    delete [] mines;
    delete [] map;
}

void GameLogic::buttonClicked(int row, int col)
{
    if(map[row][col] == FLAG_BUTTON || gameIsFinished)
        return;

    if(mines[row][col]){
        mineRow = row;
        mineCol = col;
        emit userFailed();
        return;
    }

    checkNeighbors(row, col);

    emit finished();
}

void GameLogic::checkNeighbors(int row, int col)
{
    if(map[row][col] == 0 && mines[row][col] == false){

        // Left-Up
        if((row > 0 && col > 0) && mines[row-1][col-1])
            map[row][col]++;

        // Up
        if(row > 0 && mines[row-1][col])
            map[row][col]++;

        // Right-Up
        if((row > 0 && col+1 < colNum) && mines[row-1][col+1])
            map[row][col]++;

        // Left
        if(col > 0 && mines[row][col-1])
            map[row][col]++;

        // Right
        if(col+1 < colNum && mines[row][col+1])
            map[row][col]++;

        // Left-Down
        if((row+1 < rowNum && col > 0) && mines[row+1][col-1])
            map[row][col]++;

        // Down
        if(row+1 < rowNum  && mines[row+1][col])
            map[row][col]++;

        // Right-Down
        if((row+1 < rowNum && col+1 < colNum) && mines[row+1][col+1])
            map[row][col]++;

        if(map[row][col] > 0)
            return;

        map[row][col] = EMPTY_BUTTON;

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

bool GameLogic::checkFlags()
{
    for(int i = 0 ; i < rowNum ; i++)
        for(int j = 0 ; j < colNum; j++)
            if(map[i][j] == FLAG_BUTTON && mines[i][j] == false)
                return false;

    return true;
}



