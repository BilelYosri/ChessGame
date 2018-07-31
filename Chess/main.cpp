#include "viewClasses/gwindow.h"
#include <QApplication>

#include "viewClasses/gwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GWindow w;
    QFontDatabase::addApplicationFont(":/fonts/res/bahnschrift.ttf");
    QFontDatabase::addApplicationFont(":/fonts/res/digital_counter_7.ttf");
    w.show();
    return a.exec();
}
