#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QRandomGenerator>
#include <QObject>

#define FLAG_BUTTON -2
#define EMPTY_BUTTON -1

class GameLogic : public QObject
{
    Q_OBJECT

public:
    GameLogic(int row, int col, int numOfMines);
    ~GameLogic();

    void buttonClicked(int row, int col);
    bool checkFlags();
    void setRowNum(int num) {rowNum = num;}
    void setColNum(int num) {colNum = num;}
    void setMapValue(int i , int j, int val) {map[i][j] = val;}
    void setFinished() {gameIsFinished = true;}
    int getRowNum() { return rowNum;}
    int getColNum() { return colNum;}
    int getMapValue(int i, int j) { return map[i][j];}
    bool getMinesValue(int i, int j) { return mines[i][j];}
    int getMineRow() { return mineRow;}
    int getMineCol() { return mineCol;}
    bool isFinished() { return gameIsFinished;}

private:
    void checkNeighbors(int row, int col);

    int rowNum;
    int colNum;
    int** map;
    bool** mines;
    int mineRow;
    int mineCol;
    bool gameIsFinished;

signals:
    void finished();
    void userFailed();
};

#endif // GAMELOGIC_H
