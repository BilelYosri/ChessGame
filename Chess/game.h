#ifndef GAME_H
#define GAME_H
#include "piece.h"
#include "player.h"

class Game
{
    Piece* Board[8][8];
    Piece* WhitePieces[16];
    Piece* BlackPieces[16];
    Piece* WhitePawned[15];
    Piece* BlackPawned[15];
    Player P1,P2;
    int Time1,Time2;
public:

public:
    Game();
};

#endif // GAME_H
