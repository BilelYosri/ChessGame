#include "viewClasses/gwindow.h"
#include "ui_ggame.h"
#include "gdialogexit.h"
#include "gconstants.h"
#include "dialog_time.h"
#include "dialog_promote.h"
#include "dialog_new_game.h"
#include "dialog_about.h"
#include "viewClasses/gpiece.h"
#include "gnotation.h"
#include <QScrollBar>
#include <QDesktopWidget>
#include <QFileDialog>

GWindow::GWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ENSI Chess Game - 2018");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":img/res/icon.ico"));
    QRect rec = QApplication::desktop()->screenGeometry();
    if ((rec.width() == 1366) && (rec.height() == 768))
        GWindow::showFullScreen();

    gGame = nullptr;

    whiteTimer = nullptr;
    blackTimer = nullptr;

    initButtons();
    initScene();
    connect(ui->btn_save_game,SIGNAL(pressed()),this,SLOT(save()));
    connect(ui->btn_load_game,SIGNAL(pressed()),this,SLOT(load()));
}

QGraphicsScene *GWindow::getMainScene()
{
    return mainScene;
}

QGraphicsScene *GWindow::getUpperScene()
{
    return upperScene;
}

QGraphicsScene *GWindow::getLowerScene()
{
    return lowerScene;
}

QGraphicsScene *GWindow::getNotationScene()
{
    return notationScene;
}

MTimer *GWindow::getWhiteTimer()
{
    return whiteTimer;
}

MTimer *GWindow::getBlackTimer()
{
    return blackTimer;
}

string GWindow::promote(Color _color, string _prom)
{
    if (_prom == "")
    {
        DialogPromote dialog(this);
        dialog.setModal(false);
        dialog.setBackground((Color) _color);
        dialog.exec();
        return piecePromoted;
    }
    return _prom;
}

int GWindow::getMinScroll()
{
    return ui->notationScene->verticalScrollBar()->minimum();
}

bool GWindow::gameInProgress()
{
    return (gGame != nullptr);
}

void GWindow::updateScroll(int _min, int _max)
{
    QScrollBar* scrollbar = ui->notationScene->verticalScrollBar();
    scrollbar->setValue(_max);
    scrollbar = ui->notationScene->horizontalScrollBar();
        scrollbar->setValue(scrollbar->minimum());

}

void GWindow::save()
{
    if (gGame != nullptr)
    {
        QString path = "";
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Game"), path, tr("Text Files (*.txt);;CSV Files (*.csv)"));
        if (fileName != "")
        {
            QFile file(QFileInfo(fileName).absoluteFilePath());
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                gGame->generateSaveContent(&out);
                file.close();
            }
            else
            {
                //TODO: Error message
            }
        }
    }
}

void GWindow::load()
{
    QString path = "";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Game"), path, tr("Text Files (*.txt);;CSV Files (*.csv)"));
    if (fileName != "")
    {
        //gGame = new GGame();
        QFile file(QFileInfo(fileName).absoluteFilePath());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            newGameFromFile(&in);
            gGame->loadGame(&in);
            file.close();
        }
        else
        {
            //TODO: Error message
        }
    }
}

GWindow::~GWindow()
{
    delete ui;
}

void GWindow::onTimeChanged(Color _color, QTime tm)
{
    QString t1;
    QString t2;
    t1 = QString::number(tm.minute() + tm.hour()*60).rightJustified(2,'0');
    t2 = QString::number(tm.second()).rightJustified(2,'0');
    if (_color == white)
        ui->time_white->setText(t1 + ":" + t2);
    else
        ui->time_black->setText(t1 + ":" + t2);
}

void GWindow::onTurnChanged(Color _color)
{
    if (_color == white)
    {
        ui->time_white->setStyleSheet("background-color: " + lightGreyColor);
        ui->time_black->setStyleSheet("background-color: " + activeClockColor);
    }
    else
    {
        ui->time_black->setStyleSheet("background-color: " + darkGreyColor);
        ui->time_white->setStyleSheet("background-color: " + activeClockColor);
    }
}

void GWindow::onTimeEnded(Color _color)
{
    gGame->blockGame();
    DialogTime dialog(this,this);
    dialog.setModal(true);
    dialog.setBackground((Color) -_color);
    dialog.exec();
}

void GWindow::onPiecePromoted(string _piece_type)
{
    piecePromoted = _piece_type;
}

void GWindow::scrollDown()
{
   QScrollBar* scrollBar = ui->notationScene->verticalScrollBar();
   emit scrollBar->rangeChanged(scrollBar->minimum(), scrollBar->maximum());
}

void GWindow::initButtons()
{
    ui->btn_exit->setFlat(true);
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
    mainScene = new QGraphicsScene(this);
    ui->board->setScene(mainScene);
    ui->board->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->board->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    upperScene = new QGraphicsScene(this);
    ui->whiteCapturedScene->setScene(upperScene);
    ui->whiteCapturedScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->whiteCapturedScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    upperScene->setBackgroundBrush(QBrush(QColor(216,239,238)));

    lowerScene = new QGraphicsScene(this);
    ui->blackCapturedScene->setScene(lowerScene);
    ui->blackCapturedScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->blackCapturedScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lowerScene->setBackgroundBrush(QBrush(QColor(216,239,238)));

    notationScene = new QGraphicsScene(this);
    ui->notationScene->setScene(notationScene);
    ui->notationScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notationScene->setBackgroundBrush(QBrush(QColor(216,239,238)));

    connect(ui->notationScene->verticalScrollBar(),SIGNAL(rangeChanged(int,int)), this, SLOT(updateScroll(int,int)));

}

void GWindow::newGameFromFile(QTextStream *in)
{
    QStringList fields;
    bool phasTime = false;
    int ptimeWhite = 0;
    int ptimeBlack = 0;
    int pincrement = 0;
    bool passist = false;
    for (int i=0; i<5; i++)
    {
        QString line = in->readLine();
        fields = line.split(',');
        switch(i)
        {
            case 0: if (fields.at(1)[0] == '1') phasTime = true; break;
            case 1: ptimeWhite = ((QString)fields.at(1)).toInt(); break;
            case 2: ptimeBlack = ((QString)fields.at(1)).toInt(); break;
            case 3: pincrement = ((QString)fields.at(1)).toInt(); break;
            case 4: if (fields.at(1)[0] == '1') passist = true; break;
        }
    }
    gGame = new GGame(this,phasTime,ptimeWhite,ptimeBlack,pincrement,passist);
    if (phasTime)
    {
        if (!ptimeWhite || !ptimeBlack)
            gGame->blockGame();
    }
}

void GWindow::initTimers(int _timeWhite, int _timeBlack, int _increment)
{
    if ( (whiteTimer != nullptr) && (blackTimer != nullptr) )
    {
        disconnect (whiteTimer,SIGNAL(timeChanged(Color, QTime)), this, SLOT(onTimeChanged(Color, QTime)));
        disconnect (whiteTimer,SIGNAL(turnChanged(Color)), this, SLOT(onTurnChanged(Color)));
        disconnect (whiteTimer,SIGNAL(timeEnded(Color)), this, SLOT(onTimeEnded(Color)));

        disconnect (blackTimer,SIGNAL(timeChanged(Color, QTime)), this, SLOT(onTimeChanged(Color, QTime)));
        disconnect (blackTimer,SIGNAL(turnChanged(Color)), this, SLOT(onTurnChanged(Color)));
        disconnect (blackTimer,SIGNAL(timeEnded(Color)), this, SLOT(onTimeEnded(Color)));
    }

    whiteTimer = new MTimer(white,_timeWhite, _increment);
    blackTimer = new MTimer(black,_timeBlack, _increment);

    QString t1 = QString::number(_timeWhite/60).rightJustified(2,'0');
    QString t2 = QString::number(_timeWhite%60).rightJustified(2,'0');
    ui->time_white->setText(t1 + ":" + t2);

    t1 = QString::number(_timeBlack/60).rightJustified(2,'0');
    t2 = QString::number(_timeBlack%60).rightJustified(2,'0');
    ui->time_black->setText(t1 + ":" + t2);

    if (_timeWhite && _timeBlack)
    {
        connect (whiteTimer,SIGNAL(timeChanged(Color, QTime)), this, SLOT(onTimeChanged(Color, QTime)));
        connect (whiteTimer,SIGNAL(turnChanged(Color)), this, SLOT(onTurnChanged(Color)));
        connect (whiteTimer,SIGNAL(timeEnded(Color)), this, SLOT(onTimeEnded(Color)));

        connect (blackTimer,SIGNAL(timeChanged(Color, QTime)), this, SLOT(onTimeChanged(Color, QTime)));
        connect (blackTimer,SIGNAL(turnChanged(Color)), this, SLOT(onTurnChanged(Color)));
        connect (blackTimer,SIGNAL(timeEnded(Color)), this, SLOT(onTimeEnded(Color)));
    }

}

void GWindow::newGame(bool _hasTime, int _time, int _increment, bool _assist)
{
    /*
    if (gGame != nullptr)
        delete gGame;
    */
    gGame = new GGame(this, _hasTime, _time, _time, _increment, _assist);
}

void GWindow::on_btn_exit_pressed()
{
    DialogExit dialog(this);
    dialog.setModal(true);
    dialog.exec();
}


void GWindow::on_btn_new_game_pressed()
{
    DialogNewGame dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

void GWindow::on_btn_first_move_pressed()
{
    if (gGame != nullptr)
        gGame->goToFirst();
}

void GWindow::on_btn_previous_move_pressed()
{
    if (gGame != nullptr)
        gGame->goToPrevious();
}

void GWindow::on_btn_next_move_pressed()
{
    if (gGame != nullptr)
        gGame->goToNext();
}

void GWindow::on_btn_last_move_pressed()
{
    if (gGame != nullptr)
        gGame->goToLast();
}

void GWindow::on_btn_about_pressed()
{
    DialogAbout dialog(this);
    dialog.setModal(true);
    dialog.exec();
}
