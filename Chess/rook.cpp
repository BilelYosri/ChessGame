#include "rook.h"

Rook::Rook(Color _color, int _x, int _y):Piece(_color, _x, _y)
{
    moved=false;
}

void Rook::generatePossibilities()
{

}

void Rook::move(int _x, int _y)
{

}

bool Rook::isMoved()
{
    return moved;
}

void Rook::setMoved()
{
    moved=true;
}
