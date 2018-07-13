#ifndef KING_H
#define KING_H

#include "piece.h"



class King : public Piece
{
private:
    bool moved;
public:
    King(Game* _game, Color _color, int _x, int _y);
    bool generatePossibilities();
    void move(int _x, int _y);
    bool isMoved();
    void setMoved();
    bool isInCheck();
};

#endif // KING_H
