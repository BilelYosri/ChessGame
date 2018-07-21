#ifndef QUEEN_H
#define QUEEN_H

#include "mpiece.h"



class MQueen : public MPiece
{
public:
    MQueen(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
};

#endif // QUEEN_H
