#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QWidget>

namespace Ui {
class HighScores;
}

class HighScores : public QWidget
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = nullptr);
    ~HighScores();

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H
