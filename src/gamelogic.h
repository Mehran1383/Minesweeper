#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QRandomGenerator>
#include <QObject>


class GameLogic : public QObject
{
    Q_OBJECT

public:
    GameLogic(int row, int col, int numOfMins);
    ~GameLogic();

    void buttonClicked(int row, int col);
    void checkNeighbors(int row, int col);
    bool checkFlags();


    int rowNum;
    int colNum;
    int** map;
    bool** mins;
    int minRow;
    int minCol;


signals:
    void finished();
    void userFailed();
};

#endif // GAMELOGIC_H
