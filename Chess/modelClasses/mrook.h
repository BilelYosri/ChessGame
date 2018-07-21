#ifndef ROOK_H
#define ROOK_H

#include "mpiece.h"



class MRook : public MPiece
{
private:
    bool moved;
public:
    MRook(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
    bool isMoved();
    void setMoved();
};

#endif // ROOK_H
