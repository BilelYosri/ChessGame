#include "mgame.h"
#include "mpiece.h"
#include "mpawn.h"
#include "mrook.h"
#include "mknight.h"
#include "mbishop.h"
#include "mqueen.h"
#include "mking.h"
#include <QDebug>
#include <cstring>

MGame::MGame(int _time, MPlayer _p1, MPlayer _p2)
{
    time1 = _time;
    time2 = _time;
    p1 = _p1;
    p2 = _p2;

    numberWhiteCaptured = 0;
    numberBlackCaptured = 0;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            board[i][j] = nullptr;
        }
    }

    time0 = 300;
    turn = white;
    cantPlay = false;
    MPiece* p;
    int i;
    for (i=0; i<8; i++)
    {
        p = new MPawn(this,white,i,1,i);
        board[i][1] = p;
        whitePieces[i] = p;
        p = new MPawn(this,black,i,6,i);
        board[i][6] = p;
        blackPieces[i] = p;
    }
    p = new MRook(this,white,0,0,i);
    board[0][0] = p;
    whitePieces[i++] = p;
    p = new MRook(this,white,7,0,i);
    board[7][0] = p;
    whitePieces[i++] = p;
    p = new MKnight(this,white,1,0,i);
    board[1][0] = p;
    whitePieces[i++] = p;
    p = new MKnight(this,white,6,0,i);
    board[6][0] = p;
    whitePieces[i++] = p;
    p = new MBishop(this,white,2,0,i);
    board[2][0] = p;
    whitePieces[i++] = p;
    p = new MBishop(this,white,5,0,i);
    board[5][0] = p;
    whitePieces[i++] = p;
    p = new MQueen(this,white,3,0,i);
    board[3][0] = p;
    whitePieces[i++] = p;
    p = new MKing(this,white,4,0,i);
    board[4][0] = p;
    whitePieces[i++] = p;

    i = 8;
    p = new MRook(this,black,0,7,i);
    board[0][7] = p;
    blackPieces[i++] = p;
    p = new MRook(this,black,7,7,i);
    board[7][7] = p;
    blackPieces[i++] = p;
    p = new MKnight(this,black,1,7,i);
    board[1][7] = p;
    blackPieces[i++] = p;
    p = new MKnight(this,black,6,7,i);
    board[6][7] = p;
    blackPieces[i++] = p;
    p = new MBishop(this,black,2,7,i);
    board[2][7] = p;
    blackPieces[i++] = p;
    p = new MBishop(this,black,5,7,i);
    board[5][7] = p;
    blackPieces[i++] = p;
    p = new MQueen(this,black,3,7,i);
    board[3][7] = p;
    blackPieces[i++] = p;
    p = new MKing(this,black,4,7,i);
    board[4][7] = p;
    blackPieces[i++] = p;

    memset(whiteCaptured,0,sizeof(whiteCaptured));
    memset(blackCaptured,0,sizeof(blackCaptured));
}

MGame::~MGame()
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
        if (whiteCaptured[i] != nullptr )
            delete whiteCaptured[i];
        if (blackCaptured[i] != nullptr )
            delete blackCaptured[i];
    }
}

Color MGame::getTurn()
{
    return turn;
}

bool MGame::canIPlay()
{
    return  !cantPlay;
}

bool MGame::isOutOfBoundaries(int _x, int _y)
{
    if (_x < 0 || _x > 7 || _y < 0 || _y > 7)
        return true;
    else
        return false;
}

MPiece* MGame::getSquare(int _x,int _y)
{
    if (isOutOfBoundaries(_x, _y))
        return nullptr;
    else
        return board[_x][_y];
}

void MGame::setSquare(MPiece* _p,int _x,int _y)
{
    board[_x][_y] = _p;
    if (_p != nullptr)
    {
        int xi = _p->getX();
        int yi = _p->getY();
        board[xi][yi] = nullptr;
        _p->setX(_x);
        _p->setY(_y);
        board[_x][_y] = _p;
    }

}

void MGame::generatePossibleMoves()
{
    bool possible = false;
    if (turn == white)
    {
        for (int i=0; i<8; i++)
        {
            if (whitePieces[i] != nullptr)
                if (((MPawn*)whitePieces[i])->isEnPassant())
                    ((MPawn*)whitePieces[i])->setEnPassant(false);
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
                if (((MPawn*)blackPieces[i])->isEnPassant())
                    ((MPawn*)blackPieces[i])->setEnPassant(false);
        }
        for (int i=0; i<16; i++)
        {
            if (blackPieces[i] != nullptr)
                possible |= blackPieces[i]->generatePossibilities();
        }
    }
    cantPlay = !possible;
}

MKing* MGame::getKing()
{
    if(turn==white)
        return (MKing*) whitePieces[15];
    else
        return (MKing*) blackPieces[15];
}


vector<pair<int, int> > MGame::assist(int _x,int _y)
{
    MPiece* p = getSquare(_x, _y);
    return p->getPossibilities();
}

bool MGame::play(int _x1,int _y1,int _x2,int _y2)
{
    MPiece* p = getSquare(_x1, _y1);
    if (p!= nullptr && p->isPossible(_x2, _y2))
    {
        p->move(_x2, _y2);

        if (turn == white)
            turn = black;
        else
            turn = white;

        ///TODO: (Consider Time as Thread) (Maybe even change its type from int to another class)
        //If first Move ever:
        //Stop time0
        //Else: Middle of the game:
        //Stop time to current turn

        generatePossibleMoves(); //This way, time of thinking will not count on players

        //Launch the adversary time

        return true;
    }
    else
        return false;
}

void MGame::capture(int _x,int _y)
{
    MPiece* p = getSquare(_x,_y);
    if (p == nullptr)
        qDebug() << "it's NULL!!!";
    else
        qDebug() << "it's Alright!";
    p->setX(-1);
    p->setY(-1);
    int r = p->getRank();
    if (turn == white)
    {
        blackPieces[r] = nullptr;
        whiteCaptured[numberWhiteCaptured++] = p;
    }
    else
    {
        whitePieces[r] = nullptr;
        blackCaptured[numberBlackCaptured++] = p;
    }
}

void MGame::promote(int _x, int _y)
{

}

bool MGame::isMate()
{
    return (cantPlay && getKing()->isInCheck());
}

bool MGame::isStalemate()
{
    return (cantPlay && !getKing()->isInCheck());
}

MPiece *MGame::getWhitePiece(int _x)
{
    return whitePieces[_x];
}

MPiece *MGame::getBlackPiece(int _x)
{
    return blackPieces[_x];
}

MPiece *MGame::getWhiteCaptured(int _x)
{
    return whiteCaptured[_x];
}

MPiece *MGame::getBlackCaptured(int _x)
{
    return blackCaptured[_x];
}

int MGame::getNumberWhiteCaptured()
{
    return numberWhiteCaptured;
}

int MGame::getNumberBlackCaptured()
{
    return numberBlackCaptured;
}
