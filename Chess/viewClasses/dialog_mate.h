#ifndef DIALOG_MATE_H
#define DIALOG_MATE_H

//Dialog displayed when a checkmate manifests

#include "gwindow.h"
#include <QDialog>
#include "modelClasses/mconstants.h"

namespace Ui {
class dialog_mate;
}

class DialogMate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMate(GWindow *_gWindow, QWidget *parent = nullptr);
    ~DialogMate();

    void setBackground(Color _color);

private slots:
    void on_newBtn_pressed();

    void on_exitBtn_pressed();

    void on_cancelBtn_pressed();

private:
    Ui::dialog_mate *ui;
    GWindow* parent;
};

#endif // DIALOG_MATE_H
