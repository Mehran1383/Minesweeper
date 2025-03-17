#include "squarebutton.h"

SquareButton::SquareButton(QWidget* parent) : QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border :1px solid gray; border-radius: 0px;");
}








