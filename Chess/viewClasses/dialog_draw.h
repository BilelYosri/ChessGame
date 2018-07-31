#ifndef DIALOG_DRAW_H
#define DIALOG_DRAW_H

//Dialog displayed when a draw manifests

#include "gwindow.h"
#include <QDialog>

namespace Ui {
class DialogDraw;
}

class DialogDraw : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDraw(GWindow *_gWindow, QWidget *parent = nullptr);
    ~DialogDraw();
    void setBackground();

private slots:
    void on_cancelBtn_pressed();

    void on_newBtn_pressed();

    void on_exitBtn_pressed();

private:
    Ui::DialogDraw *ui;
    GWindow* parent;
};

#endif // DIALOG_DRAW_H
