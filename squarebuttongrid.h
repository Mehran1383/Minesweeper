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
    SquareButtonGrid(QGridLayout* gridLayout = nullptr, int row = 8, int col = 8, int numOfMins = 10);
    ~SquareButtonGrid();

private slots:
    void updateMap();

private:
    QGridLayout* gridLayout;
    QPushButton*** buttonsMap;
    GameLogic* logic;
};



#endif // SQUAREBUTTONGRID_H
