#include "king.h"
#include "game.h"
#include "piece_types.h"
#include <cstring>
#include <typeinfo>

King::King(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{
    moved=false;
}

bool King::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xr,yr;
    int xp,yp;
    bool exists = false;
    bool canCastle;
    Piece* p;
    Rook* r;
    for (int i=0; i<8; i++)
    {
        xp = xi + KING_X[i];
        yp = yi + KING_Y[i];

        if (!(game->isOutOfBoundaries(xp,yp)))
        {
            p = game->getSquare(xp,yp);
            if ( p == nullptr )
            {
                game->setSquare(this,xp,yp);
                if (!(isInCheck()))
                    exists = possibilities[xp][yp] = true;
                game->setSquare(this,xi,yi);
            }
            else if ( (p != nullptr) && (p->getColor() != color) )
            {
                game->setSquare(this,xp,yp);
                if (!(isInCheck()))
                    exists = possibilities[xp][yp] = true;
                game->setSquare(this,xi,yi);
                game->setSquare(p,xp,yp);
            }
        }
    }
    if( !moved && !isInCheck())
    {
        for(int i=0;i<2;i++)
        {
            xr = xi + SIDE_ROOK_X[i];
            yr = yi + SIDE_ROOK_Y[i];
            r=(Rook*) game->getSquare(xr,yr);
            int side = (i==0)?-1:1;
                if(!(r->isMoved()))
                    canCastle = true;
                    for(int j=x; j!=xr && canCastle; j+=side)
                    {
                        if(j!=x)
                        {
                            if(game->getSquare(j,y) == nullptr)
                            {
                                game->setSquare(this,j,y);
                                canCastle &= !(isInCheck());
                                game->setSquare(this,xi,yi);
                            }
                        }
                    }
                    xp = xi + KING_CASTLE_X[i];
                    yp = yi + KING_CASTLE_Y[i];
                    possibilities[xp][yp] = canCastle;
        }
    }
}

void King::move(int _x, int _y)
{

}

bool King::isMoved()
{
    return moved;
}

void King::setMoved()
{
    moved = true;
}

bool King::isInCheck()
{
    bool inCheck = false;
    int xp, yp;
    int i;
    Piece* p;


    xp = x + RIGHT;
    yp = y + (color * UP);
    p = game->getSquare(xp,yp);
    if ((typeid(p) == typeid(Pawn)) && (p->getColor()!=color))
        inCheck=true;
    if (!inCheck)
    {
        xp = x + LEFT;
        yp = y + (color * UP);
        p = game->getSquare(xp,yp);
        if ((typeid(p) == typeid(Pawn)) && (p->getColor()!=color))
            inCheck=true;
    }


    if (!inCheck)
    {
        i=0;
        while(!inCheck && i<4)
        {
            xp = x;
            yp = y;
            do
            {
                xp = xp + ROOK_X[i];
                yp = yp + ROOK_Y[i];
                p = game->getSquare(xp,yp);
            }
            while(p==nullptr && !(game->isOutOfBoundaries(xp,yp)));
            if ((typeid(p) == typeid(Rook)) && (p->getColor()!=color))
                inCheck=true;
            i++;
        }
    }


    if (!inCheck)
    {
        i=0;
        while(!inCheck && i<8)
        {
            xp = x + KNIGHT_X[i];
            yp = y + KNIGHT_Y[i];
            p = game->getSquare(xp,yp);
            if ((typeid(p) == typeid(Knight)) && (p->getColor()!=color))
                inCheck=true;
            i++;
        }
    }


    if (!inCheck)
    {
        i=0;
        while(!inCheck && i<4)
        {
            xp = x;
            yp = y;
            do
            {
                xp = xp + BISHOP_X[i];
                yp = yp + BISHOP_Y[i];
                p = game->getSquare(xp,yp);
            }
            while(p==nullptr && !(game->isOutOfBoundaries(xp,yp)));
            if ((typeid(p) == typeid(Bishop)) && (p->getColor()!=color))
                inCheck=true;
            i++;
        }
    }


    if (!inCheck)
    {
        i=0;
        while(!inCheck && i<8)
        {
            xp = x;
            yp = y;
            do
            {
                xp = xp + QUEEN_X[i];
                yp = yp + QUEEN_Y[i];
                p = game->getSquare(xp,yp);
            }
            while(p==nullptr && !(game->isOutOfBoundaries(xp,yp)));
            if ((typeid(p) == typeid(Queen)) && (p->getColor()!=color))
                inCheck=true;
            i++;
        }
    }


    if (!inCheck)
    {
        i=0;
        while(!inCheck && i<8)
        {
            xp = x + KING_X[i];
            yp = y + KING_Y[i];
            if (typeid(game->getSquare(xp,yp)) == typeid(King))
                inCheck=true;
            i++;
        }

    }

    return inCheck;
}
