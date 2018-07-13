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
        p = new Pawn(white,1,i);
        board[1][i] = p;
        whitePieces[i] = p;
        p = new Pawn(black,6,i);
        board[6][i] = p;
        blackPieces[i] = p;
    }
    p = new Rook(white,0,0);
    board[0][0] = p;
    whitePieces[i++] = p;
    p = new Rook(white,0,7);
    board[0][7] = p;
    whitePieces[i++] = p;
    p = new Knight(white,0,1);
    board[0][1] = p;
    whitePieces[i++] = p;
    p = new Knight(white,0,6);
    board[0][6] = p;
    whitePieces[i++] = p;
    p = new Bishop(white,0,2);
    board[0][2] = p;
    whitePieces[i++] = p;
    p = new Bishop(white,0,5);
    board[0][5] = p;
    whitePieces[i++] = p;
    p = new Queen(white,0,3);
    board[0][3] = p;
    whitePieces[i++] = p;
    p = new King(white,0,4);
    board[0][4] = p;
    whitePieces[i++] = p;

    i = 8;
    p = new Rook(black,7,0);
    board[7][0] = p;
    blackPieces[i++] = p;
    p = new Rook(black,7,7);
    board[7][0] = p;
    blackPieces[i++] = p;
    p = new Knight(black,7,1);
    board[7][1] = p;
    blackPieces[i++] = p;
    p = new Knight(black,7,6);
    board[7][6] = p;
    blackPieces[i++] = p;
    p = new Bishop(black,7,2);
    board[7][2] = p;
    blackPieces[i++] = p;
    p = new Bishop(black,7,5);
    board[7][5] = p;
    blackPieces[i++] = p;
    p = new Queen(black,7,3);
    board[7][3] = p;
    blackPieces[i++] = p;
    p = new King(black,7,4);
    board[7][4] = p;
    blackPieces[i++] = p;

    memset(whitePawned,0,sizeof(whitePawned));
    memset(blackPawned,0,sizeof(blackPawned));
}

Game::~Game()
{

}

bool Game::canIPlay()
{
    return  !cantPlay;
}

Piece* Game::getSquare(int _x,int _y)
{
    if (_x < 0 || _x > 7 || _y < 0 || _y > 7)
        return nullptr;
    else
        return board[_x][_y];
}

void Game::setSquare(Piece* _p,int _x,int _y)
{
    board[_x][_y] = _p;
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

Piece* Game::getKing()
{
    if(turn==white)
        return whitePieces[15];
    else
        return blackPieces[15];
}


void Game::assist(int _x,int _y)
{

}

void Game::play(int _x1,int _y1,int _x2,int _y2)
{

}

void Game::capture(int _x,int _y)
{

}
