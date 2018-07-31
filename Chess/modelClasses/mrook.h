#ifndef ROOK_H
#define ROOK_H

#include "mpiece.h"



class MRook : public MPiece
{
private:
    bool moved;
public:
    //Constructor
    MRook(MGame* _game, Color _color, int _x, int _y, int _rank);
    //Inherited + Polymorphism
    bool generatePossibilities();
    //Inherited + Polymorphism
    void move(int _x, int _y);
    //getter to know if the rook has made his first move
    bool isMoved();
    //when moved the first time, this is called
    void setMoved();
};

#endif // ROOK_H
