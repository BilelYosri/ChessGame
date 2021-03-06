#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "viewClasses/gsquare.h"
#include "ggame.h"
#include "modelClasses/mtimer.h"


namespace Ui {
    class MainWindow;
}

class GWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Constructor
    explicit GWindow(QWidget *parent = 0);
    //called when a new game parameters are set from the new game dialog
    void newGame(bool _hasTime, int _time, int _increment, bool _assist);
    //Initialize timers to the given parameters of the new game
    void initTimers(int _timeWhite, int _timeBlack, int _increment);
    //getters for scenes (used by graphical objects in those scenes)
    QGraphicsScene* getMainScene();
    QGraphicsScene* getUpperScene();
    QGraphicsScene* getLowerScene();
    QGraphicsScene* getNotationScene();
    //Getters for model aspects of timers
    MTimer* getWhiteTimer();
    MTimer* getBlackTimer();
    //displays a dialog to choose a piece, string is passed when the game is loaded
    string promote(Color, string);
    //Scroll has some strange behaviour in notations section, so we tweaked it with this method
    int getMinScroll();
    //determine if a game is set to prevent saving a null game
    bool gameInProgress();
    //destructor
    ~GWindow();

public slots:
    void onTimeChanged(Color, QTime);
    void onTurnChanged(Color);
    void onTimeEnded(Color);
    void onPiecePromoted(string);
    void scrollDown();
    void updateScroll(int _min, int _max);
    void save();
    void load();

    void on_btn_exit_pressed();

    void on_btn_new_game_pressed();

    void on_btn_first_move_pressed();

    void on_btn_previous_move_pressed();

    void on_btn_next_move_pressed();

    void on_btn_last_move_pressed();

    void on_btn_about_pressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* mainScene;
    QGraphicsScene* upperScene;
    QGraphicsScene* lowerScene;
    QGraphicsScene* notationScene;
    GGame* gGame;
    MTimer* whiteTimer;
    MTimer* blackTimer;

    string piecePromoted;

    void initButtons();
    void initScene();
    void newGameFromFile(QTextStream* in);
};

#endif // MAINWINDOW_H
