#include "pawn.h"
#include "game.h"

Pawn::Pawn(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{
    moved=false;
    enPassant=false;
}

bool Pawn::generatePossibilities()
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
