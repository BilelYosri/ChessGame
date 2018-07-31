#ifndef DIALOG_PROMOTE_H
#define DIALOG_PROMOTE_H

//Dialog displayed when a pawn is about to promote (to select promoted piece)

#include <QDialog>
#include "modelClasses/mconstants.h"
using namespace std;

namespace Ui {
class DialogPromote;
}

class DialogPromote : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPromote(QWidget *parent = 0);
    ~DialogPromote();

    void setBackground(Color _color);

signals:
    void piecePromoted(string);

private slots:
    void on_btn_rook_clicked();

    void on_btn_knight_clicked();

    void on_btn_bishop_clicked();

    void on_btn_queen_clicked();

private:
    Ui::DialogPromote *ui;
};

#endif // DIALOG_PROMOTE_H
