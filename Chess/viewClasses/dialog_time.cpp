#include "dialog_time.h"
#include "ui_dialogtime.h"

DialogTime::DialogTime(GWindow *_gWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTime)
{
    ui->setupUi(this);
    this->parent = _gWindow;
    ui->exitBtn->setFlat(true);
    ui->cancelBtn->setFlat(true);
    ui->newBtn->setFlat(true);
    setWindowFlags(Qt::FramelessWindowHint);
}

DialogTime::~DialogTime()
{
    delete ui;
}

void DialogTime::setBackground(Color _color)
{
    if (_color == white)
    {
        ui->background->setPixmap(QPixmap(":/img/res/time_white.png"));
    }
    else
        ui->background->setPixmap(QPixmap(":/img/res/time_black.png"));
}


void DialogTime::on_newBtn_pressed()
{
    parent->on_btn_new_game_pressed();
}

void DialogTime::on_exitBtn_pressed()
{
    parent->close();
    close();
    exit(0);
}

void DialogTime::on_cancelBtn_pressed()
{
    close();
}
