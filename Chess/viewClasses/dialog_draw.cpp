#include "dialog_draw.h"
#include "ui_dialogdraw.h"

DialogDraw::DialogDraw(GWindow *_gWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDraw)
{
    this->parent = _gWindow;
    ui->setupUi(this);
    ui->exitBtn->setFlat(true);
    ui->cancelBtn->setFlat(true);
    ui->newBtn->setFlat(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setBackground();
}

DialogDraw::~DialogDraw()
{
    delete ui;
}

void DialogDraw::setBackground()
{
    ui->background->setPixmap(QPixmap(":/img/res/draw.png"));
}

void DialogDraw::on_cancelBtn_pressed()
{
    close();
}

void DialogDraw::on_newBtn_pressed()
{
    parent->on_btn_new_game_pressed();
}

void DialogDraw::on_exitBtn_pressed()
{
    parent->close();
    close();
    exit(0);
}
