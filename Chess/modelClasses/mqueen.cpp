#include "mqueen.h"
#include "mgame.h"
#include <cstring>

MQueen::MQueen(MGame* _game, Color _color, int _x, int _y, int _rank):MPiece(_game, "queen", _color, _x, _y, _rank)
{

}

bool MQueen::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    bool canMove;
    MPiece* p;
    MKing* k = game->getKing();
    for(int i=0;i<8;i++)
    {
        xp = xi;
        yp = yi;
        do
        {
            canMove=false;
            xp = xp + QUEEN_X[i];
            yp = yp + QUEEN_Y[i];
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


void MQueen::move(int _x, int _y)
{
    MPiece* p = game->getSquare(_x,_y);
    if ( p != nullptr )
            game->capture(_x,_y);
    game->setSquare(this,_x,_y);
}
