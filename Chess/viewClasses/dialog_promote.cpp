#include "dialog_promote.h"
#include "ui_dialogpromote.h"

DialogPromote::DialogPromote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPromote)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->btn_rook->setFlat(true);
    ui->btn_knight->setFlat(true);
    ui->btn_bishop->setFlat(true);
    ui->btn_queen->setFlat(true);

    connect (this,SIGNAL(piecePromoted(string)),parent,SLOT(onPiecePromoted(string)));
}

DialogPromote::~DialogPromote()
{
    delete ui;
}

void DialogPromote::setBackground(Color _color)
{
    if (_color == white)
    {
        ui->background->setPixmap(QPixmap(":/img/res/promote_white.png"));
    }
    else
        ui->background->setPixmap(QPixmap(":/img/res/promote_black.png"));
}

void DialogPromote::on_btn_rook_clicked()
{
    emit piecePromoted("rook");
    close();
}

void DialogPromote::on_btn_knight_clicked()
{
    emit piecePromoted("knight");
    close();
}

void DialogPromote::on_btn_bishop_clicked()
{
    emit piecePromoted("bishop");
    close();
}

void DialogPromote::on_btn_queen_clicked()
{
    emit piecePromoted("queen");
    close();
}
