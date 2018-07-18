#include "knight.h"
#include "game.h"
#include "piece_types.h"
#include <cstring>

Knight::Knight(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{

}

bool Knight::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    Piece* p;
    King* k = game->getKing();
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
            else if ( (p != nullptr) && (p->getColor() != color) )
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

void Knight::move(int _x, int _y)
{
    Piece* p = game->getSquare(_x,_y);
    if ( p != nullptr )
            game->capture(_x,_y);
    game->setSquare(nullptr,x,y);
    game->setSquare(this,_x,_y);
}
