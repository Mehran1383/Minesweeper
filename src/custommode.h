#ifndef CUSTOMMODE_H
#define CUSTOMMODE_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class CustomMode;
}

class CustomMode : public QDialog
{
    Q_OBJECT

public:
    explicit CustomMode(QWidget *parent = nullptr);
    ~CustomMode();

    int getRow() { return row;}
    int getCol() { return col;}
    int getMine() { return mines;}

private slots:
    void on_buttonBox_accepted();

    void on_rowSpinBox_valueChanged(int value);

    void on_colSpinBox_valueChanged(int value);

signals:
    void accepted();

private:
    Ui::CustomMode *ui;

    int row;
    int col;
    int mines;
};

#endif // CUSTOMMODE_H
