#include "piece.h"

Piece::Piece(Color _color, int _x, int _y)
{
    color=_color;
    x=_x;
    y=_y;
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
