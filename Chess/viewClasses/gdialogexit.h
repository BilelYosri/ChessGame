#ifndef DIALOGEXIT_H
#define DIALOGEXIT_H

#include <QDialog>
#include "viewClasses/gwindow.h"

namespace Ui {
    class DialogExit;
}

class DialogExit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExit(GWindow *_ggame = nullptr, QWidget *parent = 0);
    ~DialogExit();

private slots:
    void on_btn_cancel_pressed();

    void on_btn_just_exit_pressed();

private:
    Ui::DialogExit *ui;
    GWindow* parent;
};

#endif // DIALOGEXIT_H
