#ifndef PIECE_H
#define PIECE_H

#include "constants.h"

class Game;

class Piece
{
protected:
    Game* game;
    Color color;
    int x,y;
    int rank;
    bool possibilities[8][8];

public:
    Piece(Game* _game, Color _color, int _x, int _y, int _rank);
    virtual bool generatePossibilities()=0;
    bool isPossible(int, int);
    virtual void move(int, int)=0;
    int getX();
    void setX(int _x);
    int getY();
    void setY(int _y);
    int getRank();
    Color getColor();
};

#endif // PIECE_H
