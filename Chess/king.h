#ifndef KING_H
#define KING_H

#include "piece.h"



class King : public Piece
{
public:
    King(Color _color, int _x, int _y);
    void generatePossibilities();
    void move(int _x, int _y);
};

#endif // KING_H
