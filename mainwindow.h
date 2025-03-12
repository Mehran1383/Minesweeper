#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMap(int row, int col);

private slots:
    void on_mode1_clicked();

    void on_mode2_clicked();

    void on_mode3_clicked();


    void on_changeDifficulty_clicked();

private:
    Ui::MainWindow *ui;

    bool map1[8][8];
    QPushButton* Map1[8][8];
};

#endif // MAINWINDOW_H
