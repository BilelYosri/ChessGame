#ifndef KING_H
#define KING_H

#include "mpiece.h"



class MKing : public MPiece
{
private:
    bool moved;
public:
    MKing(MGame* _game, Color _color, int _x, int _y, int _rank);
    bool generatePossibilities();
    void move(int _x, int _y);
    bool isMoved();
    void setMoved();
    bool isInCheck();
};

#endif // KING_H
