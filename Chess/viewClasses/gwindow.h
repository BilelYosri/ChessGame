#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "viewClasses/gsquare.h"
#include "ggame.h"


namespace Ui {
    class MainWindow;
}

class GWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GWindow(QWidget *parent = 0);
    ~GWindow();

private slots:
    void on_btn_exit_pressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsScene* whiteCapturedScene;
    QGraphicsScene* blackCapturedScene;
    GGame* gGame;

    void initButtons();
    void initScene();
    void newGame();
};

#endif // MAINWINDOW_H
