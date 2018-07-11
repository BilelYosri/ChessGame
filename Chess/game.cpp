#include "game.h"
#include "piece.h"
#include <cstring>

Game::Game(int _time, Player _p1, Player _p2)
{
    time1 = _time;
    time2 = _time;
    p1 = _p1;
    p2 = _p2;

    time0 = 300;
    turn = white;
    mate = false;
    memset(board,0,sizeof(board));
    memset(whitePieces,0,sizeof(whitePieces));
    memset(blackPieces,0,sizeof(blackPieces));
    memset(whitePawned,0,sizeof(whitePawned));
    memset(blackPawned,0,sizeof(blackPawned));
}

Game::~Game()
{

}

Piece* Game::getSquare(int _x,int _y)
{
    return board[_x][_y];
}

void Game::setSquare(Piece* _p,int _x,int _y)
{
    board[_x][_y] = _p;
}

void Game::generatePossibleMoves()
{

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
