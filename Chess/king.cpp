#include "king.h"
#include "game.h"
#include "piece_types.h"

#include <typeinfo>

King::King(Game* _game, Color _color, int _x, int _y):Piece(_game, _color, _x, _y)
{
    moved=false;
}

bool King::generatePossibilities()
{

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
