#ifndef TIMER_H
#define TIMER_H

#include <QtCore>
#include "mconstants.h"
#include "mcountdown.h"

using namespace std;

class MTimer : public QObject
{
    Q_OBJECT
public:
    //Constructor
    explicit MTimer(Color _color, int _playTime, int _increment, QObject* parent=0);
    //resumes Time
    void resume();
    //Pauses Time
    void pause();
    //detect if the player has made its first move
    bool hasStarted();
    //returns time (used to set the time graphically periodically)
    QTime getTime();

signals:
    void timeChanged(Color, QTime);
    void turnChanged(Color);
    void timeEnded(Color);
    void paused();
    void resumed();

private:
    Color color;
    MCountDown countdown;
    QTimer timer;
    int playTime;
    int increment;
    bool started;

public slots:
    void updateTime();
    void start();


};

#endif // TIMER_H
