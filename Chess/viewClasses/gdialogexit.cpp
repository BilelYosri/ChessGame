#include "gdialogexit.h"
#include "ui_dialogexit.h"

DialogExit::DialogExit(GWindow *_ggame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExit)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->parent = _ggame;
    ui->btn_cancel->setFlat(true);
    ui->btn_just_exit->setFlat(true);
    ui->btn_save_exit->setFlat(true);
    if (!(this->parent->gameInProgress()))
        ui->btn_save_exit->setEnabled(false);
}

DialogExit::~DialogExit()
{
    delete ui;
}

void DialogExit::on_btn_cancel_pressed()
{
    close();
}

void DialogExit::on_btn_just_exit_pressed()
{
    parent->close();
    close();
    exit(0);
}

void DialogExit::on_btn_save_exit_pressed()
{
    parent->save();
    parent->close();
    close();
    exit(0);
}
