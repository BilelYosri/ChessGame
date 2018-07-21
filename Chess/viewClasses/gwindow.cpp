#include "viewClasses/gwindow.h"
#include "ui_ggame.h"
#include "gdialogexit.h"
#include "viewClasses/gpiece.h"

GWindow::GWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GWindow::showFullScreen();
    gGame = nullptr;
    initButtons();
    initScene();
    newGame();

}

GWindow::~GWindow()
{
    delete ui;
}

void GWindow::initButtons()
{
    ui->btn_exit->setFlat(true);
    ui->btn_surrender->setFlat(true);
    ui->btn_new_game->setFlat(true);
    ui->btn_load_game->setFlat(true);
    ui->btn_save_game->setFlat(true);
    ui->btn_about->setFlat(true);
    ui->btn_first_move->setFlat(true);
    ui->btn_previous_move->setFlat(true);
    ui->btn_next_move->setFlat(true);
    ui->btn_last_move->setFlat(true);
}

void GWindow::initScene()
{
    scene = new QGraphicsScene(this);
    ui->board->setScene(scene);
    ui->board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    whiteCapturedScene = new QGraphicsScene(this);
    ui->whiteCapturedScene->setScene(whiteCapturedScene);
    ui->whiteCapturedScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->whiteCapturedScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    whiteCapturedScene->setBackgroundBrush(QBrush(QColor(216,239,238)));

    blackCapturedScene = new QGraphicsScene(this);
    ui->blackCapturedScene->setScene(blackCapturedScene);
    ui->blackCapturedScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->blackCapturedScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    blackCapturedScene->setBackgroundBrush(QBrush(QColor(216,239,238)));

}

void GWindow::newGame()
{
    /*
    MPiece* p = new MKing(nullptr,black,4,7,0);
    GPiece* gp = new GPiece(p,scene);
    */

    if (gGame != nullptr)
        delete gGame;
    gGame = new GGame(scene, whiteCapturedScene, blackCapturedScene);
}

void GWindow::on_btn_exit_pressed()
{
    DialogExit dialog(this);
    dialog.setModal(true);
    dialog.setWindowFlags(Qt::FramelessWindowHint);
    dialog.exec();
}
