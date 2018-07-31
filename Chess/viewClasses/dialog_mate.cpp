#include "dialog_mate.h"
#include "ui_dialog_mate.h"

DialogMate::DialogMate(GWindow *_gWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_mate)
{
    ui->setupUi(this);
    this->parent = _gWindow;
    ui->exitBtn->setFlat(true);
    ui->cancelBtn->setFlat(true);
    ui->newBtn->setFlat(true);
    setWindowFlags(Qt::FramelessWindowHint);
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


void DialogMate::on_newBtn_pressed()
{
    parent->on_btn_new_game_pressed();
}

void DialogMate::on_exitBtn_pressed()
{
    parent->close();
    close();
    exit(0);
}

void DialogMate::on_cancelBtn_pressed()
{
    close();
}
