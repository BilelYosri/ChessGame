#include "rook.h"
#include "game.h"
#include <cstring>

Rook::Rook(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{
    moved=false;
}

bool Rook::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));

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
