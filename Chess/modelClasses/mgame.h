#ifndef GAME_H
#define GAME_H
#include "mpiece.h"
#include "mplayer.h"
#include "mconstants.h"
#include "mpiece_types.h"
#include <string>

class MGame
{
    Color turn;
    MPiece* board[8][8];
    bool cantPlay;
    MPiece* whitePieces[16];
    MPiece* blackPieces[16];
    MPiece* whiteCaptured[15];
    MPiece* blackCaptured[15];
    int numberWhiteCaptured;
    int numberBlackCaptured;
    MPlayer p1,p2;
    int time0,time1,time2;

public:
    MGame(int _time, MPlayer _p1, MPlayer _p2);
    ~MGame();

    Color getTurn();
    bool canIPlay();
    MPiece* getSquare(int _x,int _y);
    bool isOutOfBoundaries(int _x, int _y);
    void setSquare(MPiece* _p,int _x,int _y);
    void generatePossibleMoves();
    MKing* getKing();
    vector<pair<int, int> > assist(int _x,int _y);
    bool play(int _x1,int _y1,int _x2,int _y2);
    void capture(int _x,int _y);
    void promote(int _x, int _y); //Interacts with GUI

    MPiece* getWhitePiece(int _x);
    MPiece* getBlackPiece(int _x);
    MPiece* getWhiteCaptured(int _x);
    MPiece* getBlackCaptured(int _x);
    int getNumberWhiteCaptured();
    int getNumberBlackCaptured();
};

#endif // GAME_H
