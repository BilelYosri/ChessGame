#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"



class Queen : public Piece
{
public:
    Queen(Color _color, int _x, int _y);
    void generatePossibilities();
    void move(int _x, int _y);
};

#endif // QUEEN_H
