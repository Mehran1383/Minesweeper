#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QTimer>
#include <QGridLayout>
#include <QEvent>
#include <QMouseEvent>

#include <string>

#include "gamelogic.h"
#include "squarebutton.h"

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    GameBoard(QWidget* parent = nullptr, QGridLayout* gridLayout = nullptr, QTimer* timer = nullptr, int row = mode1Dim, int col = mode1Dim, int numOfMines = mode1Mines);
    ~GameBoard() override;

    int getMode() { return mode;}
    int getFlags() { return remaindedFlags;}

private slots:
    void updateMap();
    void startTimer();
    void showMines();

signals:
    void timerStarted();
    void flagChanged();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void resizeButtons();
    void gamefinished();

    QGridLayout* gridLayout;
    SquareButton*** buttonsMap;
    GameLogic* logic;
    QTimer* timer;
    QWidget* parent;

    QSize buttonSize;

    int remaindedFlags;
    int mode;
};

#endif // GAMEBOARD_H
