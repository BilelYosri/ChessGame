#include "dialog_draw.h"
#include "ui_dialogdraw.h"

DialogDraw::DialogDraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDraw)
{
    ui->setupUi(this);
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
