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

    int rowNum;
    int colNum;
    int** map;
    bool** mins;
    int minRow;
    int minCol;

signals:
    void finished();
    void userFailed();
    void userWon();





};

#endif // GAMELOGIC_H
