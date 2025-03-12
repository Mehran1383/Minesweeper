#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QMainWindow>

#include <mainwindow.h>

class GamePlay : public MainWindow
{
    Q_OBJECT
public:
    explicit GamePlay(QWidget *parent = nullptr);

    void createMap(int row, int col);

signals:

public slots:
};

#endif // GAMEPLAY_H
