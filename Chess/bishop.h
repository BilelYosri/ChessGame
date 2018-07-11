#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"



class Bishop : public Piece
{
public:
    Bishop(Color _color, int _x, int _y);
    bool generatePossibilities();
    void move(int _x, int _y);
};

#endif // BISHOP_H
