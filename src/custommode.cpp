#include "custommode.h"
#include "ui_custommode.h"

CustomMode::CustomMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomMode)
{
    ui->setupUi(this);

    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle(tr("Minesweeper"));
    setWindowIcon(QIcon(":/icons/logo.ico"));}

CustomMode::~CustomMode()
{
    delete ui;
}

void CustomMode::on_buttonBox_accepted()
{
    row = ui->rowSpinBox->value();
    col = ui->colSpinBox->value();
    mines = ui->mineSpinBox->value();

    emit accepted();
}

void CustomMode::on_rowSpinBox_valueChanged(int value)
{
    int maxValue = value * ui->colSpinBox->value() - 10;
    ui->mineSpinBox->setMaximum(maxValue);
    if(ui->mineSpinBox->value() > maxValue)
        ui->mineSpinBox->setValue(maxValue);
}

void CustomMode::on_colSpinBox_valueChanged(int value)
{
    int maxValue = value * ui->rowSpinBox->value() - 10;
    ui->mineSpinBox->setMaximum(maxValue);
    if(ui->mineSpinBox->value() > maxValue)
        ui->mineSpinBox->setValue(maxValue);
}
