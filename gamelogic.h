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

signals:
    void finished();

private:
    bool** mins;


};

#endif // GAMELOGIC_H
