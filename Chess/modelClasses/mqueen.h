#ifndef QUEEN_H
#define QUEEN_H

#include "mpiece.h"



class MQueen : public MPiece
{
public:
    //Constructor
    MQueen(MGame* _game, Color _color, int _x, int _y, int _rank);
    //Inherited + Polymorphism
    bool generatePossibilities();
    //Inherited + Polymorphism
    void move(int _x, int _y);
};

#endif // QUEEN_H
