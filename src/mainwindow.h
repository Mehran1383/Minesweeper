#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <QInputDialog>

#include "gameboard.h"
#include "database.h"
#include "custommode.h"

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

    void on_customMode_clicked();

    void on_changeDifficulty_clicked();

    void animateTransition();

    void on_pause_clicked();

    void updatePauseButton();

    void on_startOver_clicked();

    void changeFlagCounter();

    void showTime();

    void showTables();

    void addToTable();

    void createCustomGame();

private:
    Ui::MainWindow *ui;
    GameBoard* gameBoard;
    DatabaseManager* dbManager;
    CustomMode customMode;
    QGridLayout* mapLayout;
    QTimer timer;
    QTime time;

    int sec;
    int min;

    void init();
};

#endif // MAINWINDOW_H
