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
    virtual bool generatePossibilities()=0;
    virtual void move(int, int)=0;
    int getX();
    void setX(int _x);
    int getY();
    void setY(int _y);
    Color getColor();
};

#endif // PIECE_H
