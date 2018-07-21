#ifndef PAWN_H
#define PAWN_H

#include "mpiece.h"



class MPawn : public MPiece
{
    bool moved;
    bool enPassant;
public:
    MPawn(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
    bool isMoved();
    void setMoved();
    bool isEnPassant();
    void setEnPassant(bool _enPassant);
};

#endif // PAWN_H
