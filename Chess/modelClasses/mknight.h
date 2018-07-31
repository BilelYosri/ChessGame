#ifndef KNIGHT_H
#define KNIGHT_H

#include "mpiece.h"



class MKnight : public MPiece
{
public:
    //Constructor
    MKnight(MGame* _game, Color _color, int _x, int _y, int _rank);
    //Inherited + Polymorphism
    bool generatePossibilities();
    //Inherited + Polymorphism
    void move(int _x, int _y);
};

#endif // KNIGHT_H
