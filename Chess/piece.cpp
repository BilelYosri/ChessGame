#include "piece.h"
#include "game.h"

Piece::Piece(Game* _game, Color _color, int _x, int _y, int _rank)
{
    game = _game;
    color=_color;
    x=_x;
    y=_y;
    rank = _rank;
}

int Piece::getX()
{
    return x;
}

void Piece::setX(int _x)
{
    x=_x;
}

int Piece::getY()
{
    return y;
}

void Piece::setY(int _y)
{
    y=_y;
}

Color Piece::getColor()
{
    return color;
}

bool Piece::isPossible(int _x, int _y)
{
    return possibilities[_x][_y];
}
