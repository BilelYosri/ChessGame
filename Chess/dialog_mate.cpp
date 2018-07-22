#include "dialog_mate.h"
#include "ui_dialog_mate.h"

DialogMate::DialogMate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_mate)
{
    ui->setupUi(this);
}

DialogMate::~DialogMate()
{
    delete ui;
}

void DialogMate::setBackground(Color _color)
{
    if (_color == white)
    {
        ui->background->setPixmap(QPixmap(":/img/res/mate_white.png"));
    }
    else
        ui->background->setPixmap(QPixmap(":/img/res/mate_black.png"));
}

