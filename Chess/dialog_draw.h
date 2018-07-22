#ifndef DIALOG_DRAW_H
#define DIALOG_DRAW_H

#include <QDialog>

namespace Ui {
class DialogDraw;
}

class DialogDraw : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDraw(QWidget *parent = nullptr);
    ~DialogDraw();
    void setBackground();

private:
    Ui::DialogDraw *ui;
};

#endif // DIALOG_DRAW_H
