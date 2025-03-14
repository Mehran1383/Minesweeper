#ifndef SQUAREBUTTONGRID_H
#define SQUAREBUTTONGRID_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>

class SquareButtonGrid : public QWidget {
public:
    SquareButtonGrid(QWidget *parent = nullptr, QGridLayout* gridLayout = nullptr);
    ~SquareButtonGrid();

    void createMap(int row, int col);

private:
    QGridLayout* gridLayout;
    QPushButton*** buttonsMap;
};



#endif // SQUAREBUTTONGRID_H
