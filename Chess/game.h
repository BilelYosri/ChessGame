#ifndef GAME_H
#define GAME_H
#include "piece.h"
#include "player.h"
#include "constants.h"

class Game
{
    Color turn;
    Piece* board[8][8];
    bool mate;
    Piece* whitePieces[16];
    Piece* blackPieces[16];
    Piece* whitePawned[15];
    Piece* blackPawned[15];
    Player p1,p2;
    int time0,time1,time2;

public:
    Game();
    ~Game();
    Piece* getSquare(int x,int y);
    void setSquare(Piece* p,int x,int y);
    void generatePossibleMoves();
    void assist(int x,int y);
    void play(int x1,int y1,int x2,int y2);
    void capture(int x,int y);
};

#endif // GAME_H
