#include "gameboard.h"
#include <QDebug>
GameBoard::GameBoard(QWidget* parent, QGridLayout* layout, QTimer* timer, int row, int col, int numOfMins)
{
    this->gridLayout = layout;
    this->timer = timer;
    this->parent = parent;

    int width = parent->width() / gridLayout->columnCount();
    int height = parent->height() / gridLayout->rowCount();
    int side = qMin(width, height);

    logic = new GameLogic(row, col, numOfMins);
    logic->rowNum = row;
    logic->colNum = col;

    buttonsMap = new SquareButtonGrid**[row];
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col; j++)
            buttonsMap[i] = new SquareButtonGrid*[col];

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col; j++){
            buttonsMap[i][j] = new SquareButtonGrid;
            gridLayout->addWidget(buttonsMap[i][j], i, j);
            connect(buttonsMap[i][j], &QPushButton::clicked, [this, i, j](){
                this->logic->buttonClicked(i, j);
                this->startTimer();
            });
        }
    }
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

//    // Resize all buttons
//    for (int i = 0; i < gridLayout->rowCount(); ++i) {
//        for (int j = 0; j < gridLayout->columnCount(); ++j) {
//            QLayoutItem* item = gridLayout->itemAtPosition(i, j);
//            if (item) {
//                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
//                if (button) {
//                    button->setFixedSize(side, side);
//                }
//            }
//        }
//    }

    connect(logic, &GameLogic::userFailed, [this, timer](){
        this->showMins();
        timer->stop();
    });

    connect(logic, &GameLogic::finished,
            this, &GameBoard::updateMap);
}

GameBoard::~GameBoard()
{
    for(int i = 0 ; i < logic->rowNum ; i++)
        for(int j = 0 ; j < logic->colNum ; j++)
            delete buttonsMap[i][j];

    delete logic;
}

bool GameBoard::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        // Calculate the size of each button
        int width = parent->width() / gridLayout->columnCount();
        int height = parent->height() / gridLayout->rowCount();
        int side = qMin(width, height); // Ensure the buttons remain square

        // Resize all buttons
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

    return QObject::eventFilter(obj, event);
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
    for(int i = 0 ; i < logic->rowNum ; i++){
        for(int j = 0 ; j < logic->colNum ; j++){
            if(logic->map[i][j] == -1){
                buttonsMap[i][j]->setDisabled(1);
                buttonsMap[i][j]->setStyleSheet("background-color:#60798B; border-radius: 0px; border :1px solid gray;");
            }
            else if(logic->map[i][j] > 0){
                buttonsMap[i][j]->setText(QString::fromStdString(std::to_string(logic->map[i][j])));
                switch (logic->map[i][j]) {
                case 1 :
                    buttonsMap[i][j]->setStyleSheet("color: lightblue; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 2:
                    buttonsMap[i][j]->setStyleSheet("color: darkgreen; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 3:
                    buttonsMap[i][j]->setStyleSheet("color: orange; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 4:
                    buttonsMap[i][j]->setStyleSheet("color: red; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                    break;
                case 5:
                    buttonsMap[i][j]->setStyleSheet("color: darkred; background-color:#60798B; border-radius: 0px; border :1px solid gray;");
                }
                buttonsMap[i][j]->setDisabled(1);
            }
        }
    }
}

void GameBoard::showMins()
{
    int size;
    if(logic->rowNum <= 8)
        size = 30;
    else if(logic->rowNum > 8 && logic->rowNum <= 16)
        size = 20;
    else if(logic->rowNum > 16 && logic->rowNum <= 24)
        size = 15;
    else
        size = 10;

    for(int i = 0 ; i < logic->rowNum ; i++){
        for(int j = 0 ; j < logic->colNum; j++){
            if(logic->mins[i][j] == true){
                buttonsMap[i][j]->setIcon(QIcon(":/icons/logo.ico"));
                buttonsMap[i][j]->setIconSize(QSize(size,size));
            }
            buttonsMap[i][j]->setDisabled(1);
        }
    }
    buttonsMap[logic->minRow][logic->minCol]->setStyleSheet("background-color: darkred; border-radius: 0px;border :1px solid gray;");
}





