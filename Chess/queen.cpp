#include "queen.h"
#include "game.h"
#include <cstring>

Queen::Queen(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{

}

bool Queen::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    bool canMove;
    Piece* p;
    King* k = game->getKing();
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


void Queen::move(int _x, int _y)
{
    Piece* p = game->getSquare(_x,_y);
    if ( p != nullptr )
            game->capture(_x,_y);
    game->setSquare(nullptr,x,y);
    game->setSquare(this,_x,_y);
}
