#ifndef KING_H
#define KING_H

#include "mpiece.h"



class MKing : public MPiece
{
private:
    bool moved;
    bool canCastle;
public:
    //Constructor
    MKing(MGame* _game, Color _color, int _x, int _y, int _rank);
    //Inherited + Polymorphism
    bool generatePossibilities();
    //Inherited + Polymorphism
    void move(int _x, int _y);
    //getter to know if the king has made his first move
    bool isMoved();
    //when moved the first time, this is called
    void setMoved();
    //to detect checks, (helpful in generatePossibilities)
    bool isInCheck();
    //to determine if the king can castle or not
    bool canICastle();
};

#endif // KING_H
