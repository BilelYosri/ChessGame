#ifndef PIECE_H
#define PIECE_H

#include "constants.h"

class Piece
{
protected:
    Color color;
    int x,y;
    bool possibilities[8][8];

public:
    Piece(Color _color, int _x, int _y);
    virtual void generatePossibilities()=0;
    virtual void move(int, int)=0;
};

#endif // PIECE_H
