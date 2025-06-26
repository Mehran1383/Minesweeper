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
    GameBoard(QWidget* parent = nullptr, QGridLayout* gridLayout = nullptr, QTimer* timer = nullptr, int row = 8, int col = 8, int numOfMines = 10);
    ~GameBoard() override;

private slots:
    void updateMap();
    void startTimer();
    void showMines();

signals:
    void timerStarted();

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

    int remaindFlags;
};

#endif // GAMEBOARD_H
