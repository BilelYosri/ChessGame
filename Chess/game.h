#ifndef GAME_H
#define GAME_H
#include "piece.h"
#include "player.h"
#include "constants.h"
#include "piece_types.h"
#include <string>

class Game
{
    Color turn;
    Piece* board[8][8];
    bool cantPlay;
    Piece* whitePieces[16];
    Piece* blackPieces[16];
    Piece* whitePawned[15];
    Piece* blackPawned[15];
    Player p1,p2;
    int time0,time1,time2;

public:
    Game(int _time, Player _p1, Player _p2);
    ~Game();
    bool canIPlay();
    Piece* getSquare(int _x,int _y);
    bool isOutOfBoundaries(int _x, int _y);
    void setSquare(Piece* _p,int _x,int _y);
    void generatePossibleMoves();
    King* getKing();
    void assist(int _x,int _y);
    void play(int _x1,int _y1,int _x2,int _y2);
    void capture(int _x,int _y);
};

#endif // GAME_H
