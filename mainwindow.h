#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QTimer>

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

    void on_pause_clicked();

    void updatePauseButton();

private:
    Ui::MainWindow *ui;
    SquareButtonGrid* gameBoard;
    QTimer* timer;

};

#endif // MAINWINDOW_H
