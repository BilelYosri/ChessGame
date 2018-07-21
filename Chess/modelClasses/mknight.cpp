#include "mknight.h"
#include "mgame.h"
#include "mpiece_types.h"
#include <cstring>

MKnight::MKnight(MGame* _game, Color _color, int _x, int _y, int _rank):MPiece(_game, "knight", _color, _x, _y, _rank)
{

}

bool MKnight::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    MPiece* p;
    MKing* k = game->getKing();
    for (int i=0; i<8; i++)
    {
        xp = xi + KNIGHT_X[i];
        yp = yi + KNIGHT_Y[i];

        if (!(game->isOutOfBoundaries(xp,yp)))
        {
            p = game->getSquare(xp,yp);
            if ( p == nullptr )
            {
                game->setSquare(this,xp,yp);
                if (!(k->isInCheck()))
                    exists = possibilities[xp][yp] = true;
                game->setSquare(this,xi,yi);
            }
            else if ( (p->getColor() != color) )
            {
                game->setSquare(this,xp,yp);
                if (!(k->isInCheck()))
                    exists = possibilities[xp][yp] = true;
                game->setSquare(this,xi,yi);
                game->setSquare(p,xp,yp);
            }
        }
    }
    return exists;
}

void MKnight::move(int _x, int _y)
{
    MPiece* p = game->getSquare(_x,_y);
    if ( p != nullptr )
            game->capture(_x,_y);
    game->setSquare(this,_x,_y);
}
