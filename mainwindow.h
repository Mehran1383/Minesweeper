#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>

#include "squarebuttongrid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mode1_clicked();

    void on_mode2_clicked();

    void on_mode3_clicked();

    void on_changeDifficulty_clicked();

    void animateTransition();

private:
    Ui::MainWindow *ui;
    SquareButtonGrid* gameBoard;

};

#endif // MAINWINDOW_H
