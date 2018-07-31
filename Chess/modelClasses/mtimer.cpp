#include "mtimer.h"
#include <QtCore>
using namespace std;


MTimer::MTimer(Color _color, int _playTime, int _increment, QObject* parent) :
    countdown(_playTime), QObject(parent)
{
    playTime = _playTime;
    color = _color;
    started = false;
    increment = _increment;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(this, SIGNAL(resumed()), this, SLOT(start()));
    connect(this, SIGNAL(paused()), &timer, SLOT(stop()));
}

void MTimer::resume()
{
    emit resumed();
    emit turnChanged((Color)-color);
    started = true;
}

void MTimer::pause()
{
    emit paused();
    QTime tm  = countdown.getTimeLeft();
    countdown.setTime(tm.addSecs(increment));
    emit timeChanged(color, tm.addSecs(increment));
}

bool MTimer::hasStarted()
{
    return started;
}

QTime MTimer::getTime()
{
    return countdown.getTimeLeft();
}

void MTimer::updateTime()
{
    QTime tm = countdown.getTimeLeft();
    emit timeChanged(color, tm);
    if (!tm.hour() && !tm.minute() && !tm.second())
    {
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()));
        emit timeEnded(color);
    }
}

void MTimer::start()
{
    countdown.resetElapsed();
    timer.start(10);
}
