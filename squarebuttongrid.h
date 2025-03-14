#ifndef SQUAREBUTTONGRID_H
#define SQUAREBUTTONGRID_H

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>

#include "gamelogic.h"

class SquareButtonGrid : public QObject
{
    Q_OBJECT

public:
    SquareButtonGrid(QGridLayout* gridLayout = nullptr);
    ~SquareButtonGrid();

    void createMap(int row, int col, int numOfMins);

private slots:
    void updateMap();

private:
    QGridLayout* gridLayout;
    QPushButton*** buttonsMap;
    GameLogic* logic;
};



#endif // SQUAREBUTTONGRID_H
