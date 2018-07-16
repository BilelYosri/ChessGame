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
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    bool canMove;
    Piece* p;
    King* k = game->getKing();
    for(int i=0;i<4;i++)
    {
        xp = xi;
        yp = yi;
        do
        {
            canMove=false;
            xp = xp + ROOK_CASTLE_X[i];
            yp = yp + ROOK_CASTLE_Y[i];
            p = game->getSquare(xp,yp);
            if (p == nullptr && !(game->isOutOfBoundaries(xp,yp)))
            {
                canMove=true;
                game->setSquare(this,xp,yp);
                if (!(k->isInCheck()))
                    exists = possibilities[xp][yp] = true;
                game->setSquare(this,xi,yi);
            }
        }
        while( canMove );
        if ( (p != nullptr) && (p->getColor()!=color) )
        {
            game->setSquare(this,xp,yp);
            if (!(k->isInCheck()))
                exists = possibilities[xp][yp] = true;
            game->setSquare(this,xi,yi);
            game->setSquare(p,xp,yp);
        }
    }
    return exists;
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
