#include "dialog_about.h"
#include "ui_dialogabout.h"
#include <QDesktopServices>
#include <QUrl>

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->urlBtn->setFlat(true);
    ui->closeBtn->setFlat(true);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_urlBtn_pressed()
{
    QDesktopServices::openUrl(QUrl("https://goo.gl/z3LBQr", QUrl::TolerantMode));
}

void DialogAbout::on_closeBtn_pressed()
{
    close();
}
