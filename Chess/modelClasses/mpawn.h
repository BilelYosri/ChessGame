#ifndef PAWN_H
#define PAWN_H

#include "mpiece.h"



class MPawn : public MPiece
{
    bool moved;
    bool enPassant;
public:
    //Constructor
    MPawn(MGame* _game, Color _color, int _x, int _y, int _rank);
    //Inherited + Polymorphism
    bool generatePossibilities();
    //Inherited + Polymorphism
    void move(int _x, int _y);
    //getter to know if the pawn has made his first move (to know if we can jump by two squares)
    bool isMoved();
    //when moved the first time, this is called
    void setMoved();
    //determine if this pawn is vulnerable by opponent En Passant move
    bool isEnPassant();
    //update the vulnerablity state of being captured by En Passant
    void setEnPassant(bool _enPassant);
};

#endif // PAWN_H
