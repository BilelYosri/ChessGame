#ifndef MCOUNTDOWN_H
#define MCOUNTDOWN_H

#include <QtCore>

class MCountDown
{

public:
    //Constructor
    MCountDown(int _minutes);
    //Called by timers to set new time or to initialize it
    void setTime(QTime _tm);
    //Generally adds a negative number of seconds to decrement each second
    //adds increment
    void addSeconds(int _seconds);
    //Reset Elapsed each time the Timer is resumed to keep time running only when it's the player's turn
    void resetElapsed();
    //Needed to update the graphical aspect of timers
    QTime getTimeLeft();

private:
    QElapsedTimer timeElapsed;
    QTime timeLeft;

};

#endif // MCOUNTDOWN_H
