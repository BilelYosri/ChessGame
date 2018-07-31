#include "mstate.h"
#include "mgame.h"
#include <QtCore>


MState::MState(MGame *_mGame)
{
    mGame = _mGame;
    castle = false;
    turn = _mGame->getTurn();
    notation = _mGame->notation;
    fiftyMove = _mGame->fiftyMove;
    stateNumber = _mGame->stateNumber;
    nbWC = _mGame->numberWhiteCaptured;
    nbBC = _mGame->numberBlackCaptured;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            MPiece* p = mGame->getSquare(i,j);
            if (p == nullptr)
                board[i][j] = '.';
            else
            {
                board[i][j] = p->getName()[0];

                if (p->getName() == "knight")
                    board[i][j] = 'n';
                if (p->getName() == "pawn")
                {
                    if (((MPawn*) p)->isEnPassant())
                        board[i][j] = 'e';
                    else if (!((MPawn*) p)->isMoved())
                        board[i][j] = UPAWN;
                }
                if (p->getName() == "rook")
                {
                    if (!((MRook*) p)->isMoved())
                        board[i][j] = UROOK;
                }
                if (p->getName() == "king")
                {
                    if (!((MKing*) p)->isMoved())
                        board[i][j] = UKING;
                    castle |= ((MKing*) p)->canICastle();
                }
                if (p->getColor() == black)
                    board[i][j] = toupper(board[i][j]);
            }

        }
    }
    for (int i=0; i<15; i++)
    {
        MPiece* p = mGame->getWhiteCaptured(i);
        whiteCaptured[i]= (p == nullptr)?'.':p->getName()[0];
        if((p != nullptr) && (p->getName() == "knight"))
            whiteCaptured[i]='n';
        p = mGame->getBlackCaptured(i);
        blackCaptured[i]= (p == nullptr)?'.':p->getName()[0];
        if((p != nullptr) && (p->getName() == "knight"))
            whiteCaptured[i]='n';
    }
    debug();
}

void MState::updateGame()
{
    mGame->turn = turn;
    for(int i=0; i<16; i++)
    {
        mGame->whitePieces[i] = nullptr;
        mGame->blackPieces[i] = nullptr;
    }
    int rw = 0;
    int rb = 0;
    MPiece* p = nullptr;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            Color color = (islower(board[i][j])?white:black);
            switch (toupper(board[i][j])) {
            case 'P':
                p = new MPawn(mGame, color , i, j, (color == white)?rw:rb);
                ((MPawn*) p)->setMoved();
                ((MPawn*) p)->setEnPassant(false);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'E':
                p = new MPawn(mGame, color , i, j, (color == white)?rw:rb);
                ((MPawn*) p)->setMoved();
                ((MPawn*) p)->setEnPassant(true);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'X':
                p = new MPawn(mGame, color , i, j, (color == white)?rw:rb);
                ((MPawn*) p)->setEnPassant(false);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'R':
                p = new MRook(mGame, color , i, j, (color == white)?rw:rb);
                ((MRook*) p)->setMoved();
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'Y':
                p = new MRook(mGame, color , i, j, (color == white)?rw:rb);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'N':
                p = new MKnight(mGame, color , i, j, (color == white)?rw:rb);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'B':
                p = new MBishop(mGame, color , i, j, (color == white)?rw:rb);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'Q':
                p = new MQueen(mGame, color , i, j, (color == white)?rw:rb);
                if (color == white)
                    mGame->whitePieces[rw++] = p;
                else
                    mGame->blackPieces[rb++] = p;
                break;

            case 'K':
                p = new MKing(mGame, color , i, j, (color == white)?rw:rb);
                ((MRook*) p)->setMoved();
                if (color == white)
                    mGame->whitePieces[15] = p;
                else
                    mGame->blackPieces[15] = p;
                break;

            case 'Z':
                p = new MKing(mGame, color , i, j, (color == white)?rw:rb);
                if (color == white)
                    mGame->whitePieces[15] = p;
                else
                    mGame->blackPieces[15] = p;
                break;

            default:
                p = nullptr;
                break;
            }
            mGame->setSquare(p,i,j);
        }
    }

    for (int i=0; i<15; i++)
    {
        mGame->whiteCaptured[i] = nullptr;
        mGame->blackCaptured[i] = nullptr;
    }

    int i=0;
    while (whiteCaptured[i] != '.')
    {
        switch (whiteCaptured[i]) {
        case 'p':
            p = new MPawn(mGame, white , i, i, i);
            break;

        case 'r':
            p = new MRook(mGame, white , i, i, i);
            break;

        case 'n':
            p = new MKnight(mGame, white , i, i, i);
            break;

        case 'b':
            p = new MBishop(mGame, white , i, i, i);
            break;

        case 'q':
            p = new MQueen(mGame, white , i, i, i);
            break;

        case 'k':
            p = new MKing(mGame, white , i, i, i);
            break;

        default:
            p = nullptr;
            break;
        }
        mGame->whiteCaptured[i] = p;
        i++;
    }

    mGame->numberWhiteCaptured = nbWC;

    i=0;
    while (blackCaptured[i] != '.')
    {
        switch (blackCaptured[i]) {
        case 'p':
            p = new MPawn(mGame, black , i, i, i);
            break;

        case 'r':
            p = new MRook(mGame, black , i, i, i);
            break;

        case 'n':
            p = new MKnight(mGame, black , i, i, i);
            break;

        case 'b':
            p = new MBishop(mGame, black , i, i, i);
            break;

        case 'q':
            p = new MQueen(mGame, black , i, i, i);
            break;

        case 'k':
            p = new MKing(mGame, black , i, i, i);
            break;

        default:
            p = nullptr;
            break;
        }
        mGame->blackCaptured[i] = p;
        i++;
    }

    mGame->numberBlackCaptured = nbBC;

    mGame->notation = notation;
    mGame->fiftyMove = fiftyMove;

    mGame->stateNumber = stateNumber;

    mGame->generatePossibleMoves();
    //mGame->debug();

}

void MState::debug()
{
    QString sw = "";
    QString sb = "";
    for (int i=0; i<15; i++)
    {
        sw += whiteCaptured[i];
        sb += blackCaptured[i];
    }
}

bool MState::operator==(const MState &_mState)
{
    bool equal = true;
    for (int i=0; i<8 && equal; i++)
    {
        for (int j=0; j<8 && equal; j++)
        {
            equal = (board[i][j] == _mState.board[i][j]);
        }
    }
    return (equal && (castle == _mState.castle));
}

bool MState::operator!=(const MState &_mState)
{
    return !(operator==(_mState));
}
