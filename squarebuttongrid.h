#ifndef SQUAREBUTTONGRID_H
#define SQUAREBUTTONGRID_H

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>

#include <string>

#include "gamelogic.h"

class SquareButtonGrid : public QObject
{
    Q_OBJECT

public:
    SquareButtonGrid(QGridLayout* gridLayout = nullptr, QTimer* timer = nullptr, int row = 8, int col = 8, int numOfMins = 10);
    ~SquareButtonGrid();

private slots:
    void updateMap();
    void startTimer();
    void showMins();

signals:
    void timerStarted();

private:
    QGridLayout* gridLayout;
    QPushButton*** buttonsMap;
    GameLogic* logic;
    QTimer* timer;
};



#endif // SQUAREBUTTONGRID_H
