#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

//Dialog displayed when clicked on "About"

#include <QDialog>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = 0);
    ~DialogAbout();

private slots:
    void on_urlBtn_pressed();

    void on_closeBtn_pressed();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOG_ABOUT_H
