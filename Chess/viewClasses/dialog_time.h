#ifndef DIALOG_TIME_H
#define DIALOG_TIME_H

//Dialog displayed when one of the players time ends

#include "gwindow.h"
#include <QDialog>
#include "modelClasses/mconstants.h"

namespace Ui {
class DialogTime;
}

class DialogTime : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTime(GWindow *_gWindow, QWidget *parent = nullptr);
    ~DialogTime();

    void setBackground(Color _color);
private slots:
    void on_newBtn_pressed();

    void on_exitBtn_pressed();

    void on_cancelBtn_pressed();

private:
    Ui::DialogTime *ui;
    GWindow* parent;
};

#endif // DIALOG_TIME_H
