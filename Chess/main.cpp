#include "viewClasses/gwindow.h"
#include <QApplication>

#include "viewClasses/gwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GWindow w;
    w.show();

    qDebug("Run Successful");
    return a.exec();
}
