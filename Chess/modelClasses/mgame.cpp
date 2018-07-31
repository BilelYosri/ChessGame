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

MGame::MGame()
{
    numberWhiteCaptured = 0;
    numberBlackCaptured = 0;
    fiftyMove = 0;
    stateNumber = -1;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            board[i][j] = nullptr;
        }
    }

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
        for (int i=0; i<16; i++)
        {
            if ( (whitePieces[i] != nullptr) && (whitePieces[i]->getName()=="pawn") )
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
        for (int i=0; i<16; i++)
        {
            if ( (blackPieces[i] != nullptr) && (blackPieces[i]->getName()=="pawn") )
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

void MGame::generateNotation(string _pieceName, int _x1, int _y1, int _x2, int _y2, bool _captured)
{
    notation = "";
    string newName = getSquare(_x2,_y2)->getName();

    if(_pieceName == "king")
    {
        if (_x1 == 4)
        {
            if (_x2 == 6)
            {
                notation = "O-O";
                return;
            }
            if (_x2 == 2)
            {
                notation = "O-O-O";
                return;
            }
        }
    }

    if ( (_pieceName != "pawn") && (_pieceName != "knight"))
        notation += toupper(_pieceName[0]);
    else if (_pieceName == "knight")
        notation += toupper((_pieceName[1]));
    else if ( (_pieceName == "pawn") && (_x1 != _x2) )
        notation += char('a'+_x1);

    //Manage Ambiguity here
    if (_pieceName != "pawn")
    {
        bool sameLine = true;
        bool sameColumn = true;
        int duplicants = 0;
        for (int i=0; i<16; i++)
        {
            if (turn == black)
            {
                MPiece* p = getWhitePiece(i);
                if ( (p != nullptr) && (( (p->getX() != _x2) || (p->getY() != _y2) )) && (p->getName() == _pieceName))
                {
                    if (p->isPossible(_x2,_y2))
                    {
                        duplicants++;
                        if (p->getX() != _x1)
                            sameColumn = false;
                        if (p->getY() != _y1)
                            sameLine = false;
                    }
                }
            }
            else
            {
                MPiece* p = getBlackPiece(i);
                if ( (p != nullptr) && (( (p->getX() != _x2) || (p->getY() != _y2) )) && (p->getName() == _pieceName))
                {
                    if (p->isPossible(_x2,_y2))
                    {
                        duplicants++;
                        if (p->getX() != _x1)
                            sameColumn = false;
                        if (p->getY() != _y1)
                            sameLine = false;
                    }
                }
            }
        }

        if(!sameColumn && !sameLine && duplicants>1)
        {
            notation += char('a'+_x1);
            notation += char('1'+_y1);
        }
        else
        {
            if (!sameColumn)
                notation += char('a'+_x1);
            else if (!sameLine)
                notation += char('1'+_y1);
        }

    }


    if ( (_captured) || ( (_pieceName == "pawn") && (_x1 != _x2) ) )
        notation += 'x';

    notation += char('a'+_x2);
    notation += char('1'+_y2);

    if (_pieceName != newName)
    {
        notation += '=';
        if (newName != "knight")
            notation += toupper(newName[0]);
        else
            notation += toupper((newName[1]));
    }

    if ((_pieceName == "pawn") && (!_captured) && (_x1 != _x2))
        notation += " e.p.";

    if (getKing()->isInCheck())
    {
        if (isMate())
            notation += '#';
        else
            notation += '+';
    }

    return;
}

string MGame::moveFromNotation(Color _color, string _notation)
{
    string move = "";
    if (_notation[0]== 'O')
    {
        if (_notation == "O-O")
            if (_color == white)
                move = "king,king,4,0,6,0";
            else
                move = "king,king,4,7,6,7";
        else
            if (_color == white)
                move = "king,king,4,0,2,0";
            else
                move = "king,king,4,7,2,7";
    }
    else if (isupper(_notation[0]))
    {
        int i = _notation.length()-1;
        string conf = "";
        string des = "";
        if (_notation[i] == '+' || _notation[i] == '#')
            i--;
        des = _notation.substr(i-1,2);
        i-=2;
        if (_notation[i] == 'x')
            i--;
        conf = _notation.substr(1,i);
        switch (_notation[0])
        {
            case 'R': move = decode("rook","rook",_color,conf,des); break;
            case 'N': move = decode("knight","knight",_color,conf,des); break;
            case 'B': move = decode("bishop","bishop",_color,conf,des); break;
            case 'Q': move = decode("queen","queen",_color,conf,des); break;
            case 'K': move = decode("king","king",_color,conf,des); break;
        }
    }
    else
    {
        int i = _notation.length()-1;
        string conf = "";
        string des = "";
        string prom = "pawn";
        if (_notation[i] == '+' || _notation[i] == '#')
            i--;
        if (isupper(_notation[i]))
        {
            switch (_notation[i]) {
            case 'R':
                prom = "rook";
                break;
            case 'N':
                prom = "knight";
                break;
            case 'B':
                prom = "bishop";
                break;
            case 'Q':
                prom = "queen";
                break;
            default:
                break;
            }
            i-=2;
        }
        if (_notation[i] == '.')
            i-=5;

        des = _notation.substr(i-1,2);
        i-=2;
        if (_notation[i] == 'x')
            i--;
        conf = _notation.substr(0,i+1);

        move = decode("pawn",prom,_color,conf,des);
    }

    return move;
}

string MGame::getNotation()
{
    return notation;
}

string MGame::decode(string _name, string _promName, Color _color, string _conf, string _des)
{
    string move = _name + ',' + _promName + ',';
    int desX = _des[0] - 'a';
    int desY = _des[1]-'1';
    int confX = -1;
    int confY = -1;
    if (_conf.length())
    {
        if (_conf[0]>='a' && _conf[0] <='h')
        {
            confX = _conf[0] - 'a';
            if (_conf.length()==2)
                confY = _conf[1] - '1';
        }
        else
        {
            confY = _conf[0] - '1';
        }
    }
    MPiece* p = nullptr;
    int i=0;
    while ((i<16) && (p==nullptr))
    {
        MPiece* pcurr = nullptr;
        if (_color == white)
        {
            pcurr = whitePieces[i];
        }
        else
        {
            pcurr = blackPieces[i];
        }

        if (pcurr != nullptr)
        {
            if (pcurr->isPossible(desX, desY) && pcurr->getName() == _name)
            {
                if (confX == -1 && confY == -1)
                    p = pcurr;
                else
                {
                    if (confX == -1 && pcurr->getY() == confY)
                        p = pcurr;
                    if (confY == -1 && pcurr->getX() == confX)
                        p = pcurr;
                    if (pcurr->getX() == confX && pcurr->getY() == confY)
                        p = pcurr;
                }
            }
        }

        i++;
    }
    move += char(p->getX()+'0');
    move += ',';
    move += char(p->getY()+'0');
    move += ',';
    move += char(desX + '0');
    move += ',';
    move += char(desY + '0');

    return move;

}

bool MGame::play(int _x1,int _y1,int _x2,int _y2)
{
    MPiece* p = getSquare(_x1, _y1);
    if (p!= nullptr && p->isPossible(_x2, _y2))
    {
        if ((getSquare(_x2,_y2)!=nullptr) || (p->getName() == "pawn"))
            fiftyMove = 0;
        else
            fiftyMove++;
        p->move(_x2, _y2);

        if (turn == white)
            turn = black;
        else
            turn = white;
        return true;
    }
    else
        return false;
}

void MGame::capture(int _x,int _y)
{
    MPiece* p = getSquare(_x,_y);
    if (p)
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

void MGame::promote(int _x, int _y, string _piece_type)
{
    MPiece* p = getSquare(_x,_y);
    int rank = p->getRank();
    Color color = p->getColor();

    MPiece* pr;
    if (_piece_type == "rook")
    {
        pr = new MRook(this,color,_x,_y,rank);
        ((MRook*) pr)->setMoved();
    }
    else if (_piece_type == "bishop")
    {
        pr = new MBishop(this,color,_x,_y,rank);
    }
    else if (_piece_type == "knight")
    {
        pr = new MKnight(this,color,_x,_y,rank);
    }
    else if (_piece_type == "queen")
    {
        pr = new MQueen(this,color,_x,_y,rank);
    }

    if (color == white)
    {
        MPiece* p = whitePieces[rank];
        whitePieces[rank] = pr;
        delete p;
    }
    else
    {
        MPiece* p = blackPieces[rank];
        blackPieces[rank] = pr;
        delete p;
    }
    setSquare(pr,_x,_y);
}

bool MGame::isMate()
{
    return (cantPlay && getKing()->isInCheck());
}

bool MGame::isStalemate()
{
    return (cantPlay && !getKing()->isInCheck());
}

bool MGame::isDraw()
{
    bool draw = false;

    if (isStalemate())
        draw = true;

    if (!draw)
    {
        draw = (fiftyMove == (50 * 2));
    }

    if (!draw)
    {
        draw = insufficientMaterial();
    }

    if (!draw)
    {
        draw = threeRepetition();
    }

    return draw;
}

bool MGame::insufficientMaterial()
{
    bool draw = false;

    int totalWhite=0,totalBlack=0;
    int whiteBishopWhite=0,blackBishopWhite=0;
    int whiteBishopBlack=0,blackBishopBlack=0;
    int whiteKnight=0, blackKnight=0;

    for (int i=0; i<15; i++)
    {
        MPiece* p = whitePieces[i];
        if (p != nullptr)
        {
            totalWhite++;
            if (p->getName() == "knight")
                whiteKnight++;
            if ((p->getName() == "bishop"))
            {
                if ((p->getX() + p->getY()) % 2)
                    whiteBishopWhite++;
                else
                    whiteBishopBlack++;
            }
        }

        p = blackPieces[i];
        if (p != nullptr)
        {
            totalBlack++;
            if (p->getName() == "knight")
                blackKnight++;
            if ((p->getName() == "bishop"))
            {
                if ((p->getX() + p->getY()) % 2)
                    blackBishopWhite++;
                else
                    blackBishopBlack++;
            }
        }
    }

    draw = !totalWhite && !totalBlack;

    if (!draw)
    {
        draw = ((totalWhite == 1) && (!totalBlack) && (whiteKnight == 1)) || ((totalBlack == 1) && (!totalWhite) && (blackKnight == 1));
    }

    if (!draw)
    {
        int total = totalWhite + totalBlack;
        int totalBishopWhite = whiteBishopWhite + blackBishopWhite;
        int totalBishopBlack = whiteBishopBlack + blackBishopBlack;
        draw = (total == totalBishopWhite) || (total == totalBishopBlack);
    }
    return draw;
}

bool MGame::threeRepetition()
{
    int last = states.size()-1;
    MState now = states[last];
    int reps=1;
    for (int i=0; (i<last) && (reps<3); i++)
    {
        if (now == states[i])
            reps++;
    }
    return (reps == 3);
}

void MGame::goToPrevious()
{

    if (stateNumber > 0)
    {
        stateNumber--;
        states[stateNumber].updateGame();
        //states[stateNumber-1].debug();
        //states[stateNumber].debug();
    }
}

void MGame::goToNext()
{
    if (stateNumber < states.size()-1)
    {
        stateNumber++;
        states[stateNumber].updateGame();
        //states[stateNumber-1].debug();
        //states[stateNumber].debug();
    }
}

void MGame::goToLast()
{
    if (stateNumber < states.size()-1)
    {
        states[states.size()-1].updateGame();
    }
}

bool MGame::isLastState()
{
    return (stateNumber == states.size()-1);
}

void MGame::saveState()
{
    stateNumber++;
    MState state(this);
    states.push_back(state);
}

void MGame::goToFirst()
{
    if (stateNumber > 0)
    {
        states[0].updateGame();
    }
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

int MGame::getStateNumber()
{
    return stateNumber;
}

void MGame::debug()
{
    for (int i=7; i>=0; i--)
    {
        QString s = "";
        for (int j=0; j<8; j++)
        {
            if (board[j][i] == nullptr)
                s = s + ". ";
            else
                if (board[j][i]->getColor() == white)
                    s = s + board[j][i]->getName()[0] + " ";
                else
                    s = s + toupper(board[j][i]->getName()[0]) + " ";
        }
        qDebug() << s;
        qDebug() << "\"----------------\"";
    }
    qDebug() << "\"================\"";
}
