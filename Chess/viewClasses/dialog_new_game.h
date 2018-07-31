#ifndef DIALOG_NEW_GAME_H
#define DIALOG_NEW_GAME_H

//Dialog displayed when clicked on "New Game"

#include "gwindow.h"
#include <QDialog>

namespace Ui {
class DialogNewGame;
}

class DialogNewGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewGame(QWidget *parent = 0);
    ~DialogNewGame();

private slots:
    void on_startBtn_pressed();

    void on_closeBtn_pressed();


    void on_timerCheck_stateChanged(int arg1);

private:
    Ui::DialogNewGame *ui;
    GWindow* window;
};

#endif // DIALOG_NEW_GAME_H
