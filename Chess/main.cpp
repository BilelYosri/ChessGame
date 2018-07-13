#include "mainwindow.h"
#include <QApplication>

#include "game.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    Player p1,p2;
    Game g(0,p1,p2);

    qDebug("Run Successful");
    return a.exec();
}
