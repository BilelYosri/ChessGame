#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"



class Knight : public Piece
{
public:
    Knight(Color _color, int _x, int _y);
    bool generatePossibilities();
    void move(int _x, int _y);
};

#endif // KNIGHT_H
