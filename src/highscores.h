#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QWidget>
#include <QTableView>

namespace Ui {
class HighScores;
}

class HighScores : public QWidget
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = nullptr);
    ~HighScores();

    QTableView* table(int mode);

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H
