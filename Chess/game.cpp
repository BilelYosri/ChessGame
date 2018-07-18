#include "game.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <cstring>

Game::Game(int _time, Player _p1, Player _p2)
{
    time1 = _time;
    time2 = _time;
    p1 = _p1;
    p2 = _p2;

    time0 = 300;
    turn = white;
    cantPlay = false;
    Piece* p;
    int i;
    for (i=0; i<8; i++)
    {
        p = new Pawn(this,white,1,i);
        board[1][i] = p;
        whitePieces[i] = p;
        p = new Pawn(this,black,6,i);
        board[6][i] = p;
        blackPieces[i] = p;
    }
    p = new Rook(this,white,0,0);
    board[0][0] = p;
    whitePieces[i++] = p;
    p = new Rook(this,white,0,7);
    board[0][7] = p;
    whitePieces[i++] = p;
    p = new Knight(this,white,0,1);
    board[0][1] = p;
    whitePieces[i++] = p;
    p = new Knight(this,white,0,6);
    board[0][6] = p;
    whitePieces[i++] = p;
    p = new Bishop(this,white,0,2);
    board[0][2] = p;
    whitePieces[i++] = p;
    p = new Bishop(this,white,0,5);
    board[0][5] = p;
    whitePieces[i++] = p;
    p = new Queen(this,white,0,3);
    board[0][3] = p;
    whitePieces[i++] = p;
    p = new King(this,white,0,4);
    board[0][4] = p;
    whitePieces[i++] = p;

    i = 8;
    p = new Rook(this,black,7,0);
    board[7][0] = p;
    blackPieces[i++] = p;
    p = new Rook(this,black,7,7);
    board[7][0] = p;
    blackPieces[i++] = p;
    p = new Knight(this,black,7,1);
    board[7][1] = p;
    blackPieces[i++] = p;
    p = new Knight(this,black,7,6);
    board[7][6] = p;
    blackPieces[i++] = p;
    p = new Bishop(this,black,7,2);
    board[7][2] = p;
    blackPieces[i++] = p;
    p = new Bishop(this,black,7,5);
    board[7][5] = p;
    blackPieces[i++] = p;
    p = new Queen(this,black,7,3);
    board[7][3] = p;
    blackPieces[i++] = p;
    p = new King(this,black,7,4);
    board[7][4] = p;
    blackPieces[i++] = p;

    memset(whitePawned,0,sizeof(whitePawned));
    memset(blackPawned,0,sizeof(blackPawned));
}

Game::~Game()
{
    for(int i=0;i<8;i++)
       for(int j=0;j<8;j++)
            if ( board[i][j] != nullptr )
                delete[] board[i][j];

    for(int i=0;i<16;i++)
    {
        if (whitePieces[i] != nullptr )
            delete whitePieces[i];
        if ( blackPieces[i] != nullptr )
            delete blackPieces[i];
    }
    for(int i=0;i<15;i++)
    {
        if (whitePawned[i] != nullptr )
            delete whitePawned[i];
        if (blackPawned[i] != nullptr )
            delete blackPawned[i];
    }
}

bool Game::canIPlay()
{
    return  !cantPlay;
}

bool Game::isOutOfBoundaries(int _x, int _y)
{
    if (_x < 0 || _x > 7 || _y < 0 || _y > 7)
        return true;
    else
        return false;
}

Piece* Game::getSquare(int _x,int _y)
{
    if (isOutOfBoundaries(_x, _y))
        return nullptr;
    else
        return board[_x][_y];
}

void Game::setSquare(Piece* _p,int _x,int _y)
{
    int xi = _p->getX();
    int yi = _p->getY();
    board[xi][yi] = nullptr;
    board[_x][_y] = _p;
    _p->setX(_x);
    _p->setY(_y);
}

void Game::generatePossibleMoves()
{
    bool possible = false;
    if (turn == white)
    {
        for (int i=0; i<8; i++)
        {
            if (whitePieces[i] != nullptr)
                if (((Pawn*)whitePieces[i])->isEnPassant())
                    ((Pawn*)whitePieces[i])->setEnPassant(false);
        }
        for (int i=0; i<16; i++)
        {
            if (whitePieces[i] != nullptr)
                possible |= whitePieces[i]->generatePossibilities();
        }
    }
    else
    {
        for (int i=0; i<8; i++)
        {
            if (blackPieces[i] != nullptr)
                if (((Pawn*)blackPieces[i])->isEnPassant())
                    ((Pawn*)blackPieces[i])->setEnPassant(false);
        }
        for (int i=0; i<16; i++)
        {
            if (blackPieces[i] != nullptr)
                possible |= blackPieces[i]->generatePossibilities();
        }
    }
    cantPlay = !possible;
}

King* Game::getKing()
{
    if(turn==white)
        return (King*) whitePieces[15];
    else
        return (King*) blackPieces[15];
}


void Game::assist(int _x,int _y)
{

}

void Game::play(int _x1,int _y1,int _x2,int _y2)
{
    Piece* p = getSquare(_x1, _y1);
    if (p->isPossible(_x2, _y2))
    {
        p->move(_x2, _y2);
        ///TODO: (Consider Time as Thread) (Maybe even change its type from int to another class)
        //If first Move ever:
        //Stop time0
        //Launch time2

        //Else: Middle of the game:
        //Stop time to current turn
        //Launch the other time

        turn = (Color) -turn;
    }
}

void Game::capture(int _x,int _y)
{

}
