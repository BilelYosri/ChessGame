#include "mcountdown.h"

MCountDown::MCountDown(int _seconds)
{
    timeLeft = QTime(_seconds/3600,(_seconds%3600)/60,_seconds%60);
}

void MCountDown::setTime(QTime _tm)
{
    timeLeft = _tm;
}

void MCountDown::addSeconds(int _seconds)
{
    timeLeft.addSecs(_seconds);
}

void MCountDown::resetElapsed()
{
    timeElapsed.restart();
}

QTime MCountDown::getTimeLeft()
{
    return timeLeft.addMSecs(-(timeElapsed.elapsed()));
}
