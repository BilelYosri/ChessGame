#ifndef DIALOG_MATE_H
#define DIALOG_MATE_H

#include <QDialog>
#include "modelClasses/mconstants.h"

namespace Ui {
class dialog_mate;
}

class DialogMate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMate(QWidget *parent = nullptr);
    ~DialogMate();

    void setBackground(Color _color);

private:
    Ui::dialog_mate *ui;
};

#endif // DIALOG_MATE_H
