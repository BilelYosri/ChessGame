#include "mpawn.h"
#include "mgame.h"
#include <cstring>
#include <typeinfo>

MPawn::MPawn(MGame* _game, Color _color, int _x, int _y, int _rank):MPiece(_game, "pawn", _color, _x, _y, _rank)
{
    moved=false;
    enPassant=false;
}

bool MPawn::generatePossibilities()
{
    memset(possibilities,false,sizeof (possibilities));
    int xi = x;
    int yi = y;
    int xp,yp;
    bool exists = false;
    MPiece* p;
    MKing* k = game->getKing();

    xp = xi + PAWN_ADVANCE_X[0];
    yp = yi + color * PAWN_ADVANCE_Y[0];
    p = game->getSquare(xp,yp);
    if ( p == nullptr )
    {
        game->setSquare(this,xp,yp);
        if (!(k->isInCheck()))
            exists = possibilities[xp][yp] = true;
        game->setSquare(this,xi,yi);
    }

    for (int i=0; i<2; i++)
    {
        xp = xi + PAWN_CAPTURE_X[i];
        yp = yi + color * PAWN_CAPTURE_Y[i];
        p = game->getSquare(xp,yp);
        if ( (p != nullptr) && (p->getColor() != color) )
        {
            game->setSquare(this,xp,yp);
            if (!(k->isInCheck()))
                exists = possibilities[xp][yp] = true;
            game->setSquare(this,xi,yi);
            game->setSquare(p,xp,yp);
        }
    }

    if (!moved)
    {
        xp = xi + PAWN_JUMP_X[0];
        yp = yi + color * PAWN_JUMP_Y[0];
        int xpp = xi + PAWN_ADVANCE_X[0];
        int ypp = yi + color * PAWN_ADVANCE_Y[0];
        MPiece* pp = game->getSquare(xpp,ypp);
        p = game->getSquare(xp,yp);
        if ( ( p == nullptr ) && ( pp == nullptr ) )
        {
            game->setSquare(this,xp,yp);
            if (!(k->isInCheck()))
                exists = possibilities[xp][yp] = true;
            game->setSquare(this,xi,yi);
        }
    }

    else
    {
        for (int i=0; i<2; i++)
        {
            int xa = xi + PAWN_ADJACENT_X[i];
            int ya = yi + PAWN_ADJACENT_Y[i];
            MPiece* pp = game->getSquare(xa,ya);
            if ( (pp != nullptr) && (pp->getName() == "pawn") && (pp->getColor() != color) )
            {
                if ( ((MPawn*) pp)->isEnPassant() )
                {
                    xp = xi + PAWN_CAPTURE_X[i];
                    yp = yi + color * PAWN_CAPTURE_Y[i];
                    p = game->getSquare(xp,yp);
                    if ( p == nullptr )
                    {
                        game->setSquare(this,xp,yp);
                        game->setSquare(nullptr,xa,ya);
                        if (!(k->isInCheck()))
                            exists = possibilities[xp][yp] = true;
                        game->setSquare(this,xi,yi);
                        game->setSquare(pp,xa,ya);
                    }
                }
            }


        }
    }

    return exists;
}

void MPawn::move(int _x, int _y)
{
    moved = true;
    int canPromote = (color == white)? 7: 0;
    bool capture = (x != _x);
    int oldY = y;

    MPiece* p = game->getSquare(_x,_y);
    if (capture)
    {
        if ( p != nullptr )
            game->capture(_x,_y);
        else
            game->capture(_x, y);
    }

    game->setSquare(this,_x,_y);

    if (abs(_y - oldY) > 1)
        setEnPassant(true);

    if (_y == canPromote)
    {
        game->promote(_x,_y);
    }

}

bool MPawn::isMoved()
{
    return moved;
}

void MPawn::setMoved()
{
    moved = true;
}

bool MPawn::isEnPassant()
{
    return enPassant;
}

void MPawn::setEnPassant(bool _enPassant)
{
    enPassant = _enPassant;
}
