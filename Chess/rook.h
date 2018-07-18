#ifndef ROOK_H
#define ROOK_H

#include "piece.h"



class Rook : public Piece
{
private:
    bool moved;
public:
    Rook(Game* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
    bool isMoved();
    void setMoved();
};

#endif // ROOK_H
