#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QTimer>
#include <QGridLayout>

#include <string>

#include "gamelogic.h"
#include "squarebuttongrid.h"

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    GameBoard(QWidget* parent = nullptr, QGridLayout* gridLayout = nullptr, QTimer* timer = nullptr, int row = 8, int col = 8, int numOfMins = 10);
    ~GameBoard() override;

private slots:
    void updateMap();
    void startTimer();
    void showMins();

signals:
    void timerStarted();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QGridLayout* gridLayout;
    SquareButtonGrid*** buttonsMap;
    GameLogic* logic;
    QTimer* timer;
    QWidget* parent;
};

#endif // GAMEBOARD_H
