#ifndef BISHOP_H
#define BISHOP_H

#include "mpiece.h"



class MBishop : public MPiece
{
public:
    MBishop(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
};

#endif // BISHOP_H
