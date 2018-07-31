#include "dialog_new_game.h"
#include "ui_dialognewgame.h"

DialogNewGame::DialogNewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    window = (GWindow*) parent;
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->startBtn->setFlat(true);
    ui->closeBtn->setFlat(true);
    ui->timeSpin->setEnabled(false);
    ui->incrementSpin->setEnabled(false);
}

DialogNewGame::~DialogNewGame()
{
    delete ui;
}

void DialogNewGame::on_startBtn_pressed()
{
    bool hasTime = ui->timerCheck->isChecked();
    int time = ui->timeSpin->value();
    int increment = ui->incrementSpin->value();
    bool assist = ui->assistCheck->isChecked();


    window->newGame(hasTime, time*60, increment, assist);
    close();
}

void DialogNewGame::on_closeBtn_pressed()
{
    close();
}

void DialogNewGame::on_timerCheck_stateChanged(int arg1)
{
    bool hasTime = ui->timerCheck->isChecked();
    if (hasTime)
    {
        ui->timeSpin->setEnabled(true);
        ui->incrementSpin->setEnabled(true);
    }
    else
    {
        ui->timeSpin->setEnabled(false);
        ui->incrementSpin->setEnabled(false);
    }
}
