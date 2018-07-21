#ifndef KNIGHT_H
#define KNIGHT_H

#include "mpiece.h"



class MKnight : public MPiece
{
public:
    MKnight(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
};

#endif // KNIGHT_H
