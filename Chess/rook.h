#ifndef ROOK_H
#define ROOK_H

#include "piece.h"



class Rook : public Piece
{
public:
    Rook(Color _color, int _x, int _y);
    void generatePossibilities();
    void move(int _x, int _y);
};

#endif // ROOK_H
