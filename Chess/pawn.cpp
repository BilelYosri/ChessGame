#include "pawn.h"

Pawn::Pawn(Color _color, int _x, int _y):Piece(_color, _x, _y)
{

}

void Pawn::generatePossibilities()
{

}

void Pawn::move(int _x, int _y)
{

}

bool Pawn::isMoved()
{
    return moved;
}

void Pawn::setMoved()
{
    moved = true;
}

bool Pawn::isEnPassant()
{
    return enPassant;
}

void Pawn::setEnPassant(bool _enPassant)
{
    enPassant = _enPassant;
}
