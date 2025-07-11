#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(QWidget* parent, QGridLayout* layout, QTimer* timer, int row, int col, int numOfMines)
{
    this->gridLayout = layout;
    this->timer = timer;
    this->parent = parent;
    this->remaindedFlags = numOfMines;

    switch (row) {
    case mode1Dim: mode = 1; break;
    case mode2Dim: mode = 2; break;
    case mode3Dim: mode = 3; break;
    default: mode = 4;
    }

    logic = new GameLogic(row, col, numOfMines);
    logic->setRowNum(row);
    logic->setColNum(col);

    buttonsMap = new SquareButton**[row];
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col; j++)
            buttonsMap[i] = new SquareButton*[col];

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col; j++){
            buttonsMap[i][j] = new SquareButton;
            buttonsMap[i][j]->installEventFilter(this);
            gridLayout->addWidget(buttonsMap[i][j], i, j);
            connect(buttonsMap[i][j], &QPushButton::clicked, [this, i, j, timer](){
                this->logic->buttonClicked(i, j);
                if(!logic->isFinished() && !timer->isActive())
                    this->startTimer();
            });
        }
    }
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    resizeButtons();

    connect(logic, &GameLogic::userFailed,
            this, &GameBoard::showMines);

    connect(logic, &GameLogic::finished,
            this, &GameBoard::updateMap);
}

GameBoard::~GameBoard()
{
    for(int i = 0 ; i < logic->getRowNum() ; i++)
        for(int j = 0 ; j < logic->getColNum() ; j++)
            delete buttonsMap[i][j];

    delete logic;
}

bool GameBoard::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        resizeButtons();
        emit windowResized();
    }

    if (obj->inherits("QPushButton") && event->type() == QEvent::MouseButtonPress && !logic->isFinished()) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            for(int i = 0 ; i < logic->getRowNum() ; i++){
                for(int j = 0 ; j < logic->getColNum() ; j++){
                    if (buttonsMap[i][j] == obj) {
                        if(logic->getMapValue(i, j) == 0 && remaindedFlags > 0){
                            buttonsMap[i][j]->setIcon(QIcon(":/icons/flag.png"));
                            buttonsMap[i][j]->setCursor(Qt::ArrowCursor);
                            logic->setMapValue(i, j, FLAG_BUTTON);
                            remaindedFlags--;
                            emit flagChanged();
                            if(remaindedFlags == 0 && logic->checkFlags()){
                                gamefinished();
                                logic->setFinished();
                                timer->stop();
                                emit userWon();
                                emit gameOver();
                            }
                        }
                        else if(logic->getMapValue(i, j) == FLAG_BUTTON){
                            buttonsMap[i][j]->setIcon(QIcon());
                            buttonsMap[i][j]->setCursor(Qt::PointingHandCursor);
                            logic->setMapValue(i, j, 0);
                            remaindedFlags++;
                            emit flagChanged();
                        }
                        if(!logic->isFinished() && !timer->isActive())
                            this->startTimer();

                        return true;
                    }
                }
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

void GameBoard::resizeButtons()
{
    int width = parent->width() / gridLayout->columnCount();
    int height = parent->height() / gridLayout->rowCount();
    int side = qMin(width, height);
    buttonSize = QSize(side,side);

    for (int i = 0; i < gridLayout->rowCount(); ++i) {
        for (int j = 0; j < gridLayout->columnCount(); ++j) {
            QLayoutItem* item = gridLayout->itemAtPosition(i, j);
            if (item) {
                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                if (button) {
                    button->setFixedSize(side, side);
                }
            }
        }
    }
}

void GameBoard::startTimer()
{
    if(!timer->isActive()){
        timer->start();
        emit timerStarted();
    }
}

void GameBoard::updateMap()
{
    for(int i = 0 ; i < logic->getRowNum() ; i++){
        for(int j = 0 ; j < logic->getColNum() ; j++){
            if(logic->getMapValue(i, j) == EMPTY_BUTTON){
                buttonsMap[i][j]->setDisabled(1);
                buttonsMap[i][j]->setStyleSheet("background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
            }
            else if(logic->getMapValue(i, j) > 0){
                buttonsMap[i][j]->setText(QString::fromStdString(std::to_string(logic->getMapValue(i, j))));
                switch (logic->getMapValue(i, j)) {
                case 1 :
                    buttonsMap[i][j]->setStyleSheet("color: lightblue; background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
                    break;
                case 2:
                    buttonsMap[i][j]->setStyleSheet("color: darkgreen; background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
                    break;
                case 3:
                    buttonsMap[i][j]->setStyleSheet("color: orange; background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
                    break;
                case 4:
                    buttonsMap[i][j]->setStyleSheet("color: red; background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
                    break;
                case 5:
                    buttonsMap[i][j]->setStyleSheet("color: darkred; background-color:#60798B; border-radius: 0px; border :1px solid #19232D;");
                }
                buttonsMap[i][j]->setDisabled(1);
            }
        }
    }
}

void GameBoard::showMines()
{
    QIcon mineIcon(":/icons/logo.ico");
    QPixmap minePixmap = mineIcon.pixmap(buttonSize);

    QIcon wrongIcon(":/icons/wrong.png");
    QPixmap wrongPixmap = wrongIcon.pixmap(buttonSize);

    for(int i = 0 ; i < logic->getRowNum() ; i++){
        for(int j = 0 ; j < logic->getColNum(); j++){
            if(logic->getMinesValue(i, j) == true && logic->getMapValue(i, j) != FLAG_BUTTON)
                buttonsMap[i][j]->setIcon(QIcon(minePixmap));
            else if(logic->getMinesValue(i, j) == false && logic->getMapValue(i, j) == FLAG_BUTTON)
                buttonsMap[i][j]->setIcon(QIcon(wrongPixmap));
            if(logic->getMapValue(i, j) != FLAG_BUTTON)
                buttonsMap[i][j]->setDisabled(1);
        }
    }
    buttonsMap[logic->getMineRow()][logic->getMineCol()]->setStyleSheet("background-color: darkred; border-radius: 0px; border :1px solid #19232D;");
    logic->setFinished();
    timer->stop();
    emit gameOver();
}

void GameBoard::gamefinished()
{
    QIcon icon(":/icons/tada.png");
    QPixmap pixmap = icon.pixmap(buttonSize);

    for(int i = 0 ; i < logic->getRowNum() ; i++){
        for(int j = 0 ; j < logic->getColNum(); j++){
            if(logic->getMinesValue(i, j) == true)
                buttonsMap[i][j]->setIcon(QIcon(pixmap));

            else buttonsMap[i][j]->setDisabled(1);
        }
    }
}




