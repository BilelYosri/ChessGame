#ifndef MSTATE_H
#define MSTATE_H

#include "mpiece.h"
#include "mpiece_types.h"
#include "mconstants.h"

class MGame;

class MState
{
public:
    //Constructor
    MState(MGame* _mGame);
    //generate game properties from the state instance
    void updateGame();
    //used in debugging
    void debug();
    //Used to detect 3 repetitions
    bool operator==(const MState& _mState);
    bool operator!=(const MState& _mState);

private:
    MGame* mGame;
    char board[8][8];
    char whiteCaptured[15];
    char blackCaptured[15];
    Color turn;
    bool castle;
    string notation;
    int fiftyMove;
    int stateNumber;
    int nbWC;
    int nbBC;

    const char UPAWN = 'x';
    const char UROOK = 'y';
    const char UKING = 'z';
};

#endif // MSTATE_H
