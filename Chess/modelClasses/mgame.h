#ifndef GAME_H
#define GAME_H
#include "mpiece.h"
#include "mconstants.h"
#include "mpiece_types.h"
#include "mstate.h"
#include <string>

class MGame
{

    friend class MState;

public:
    //Constructor
    MGame();
    //Destructor
    ~MGame();

    //Getter for turn
    Color getTurn();
    //Return true if the game isn't stuck (logically by chess rules)
    bool canIPlay();
    //Get a Piece at a given square
    MPiece* getSquare(int _x,int _y);
    //return true if a coordinate is within the board (0 <= x,y <= 7)
    bool isOutOfBoundaries(int _x, int _y);
    //set a piece on a square and reset its initial position to nullptr
    void setSquare(MPiece* _p,int _x,int _y);
    //Calls the generatePossibilities method for each piece the player in turn has
    void generatePossibleMoves();
    //Get a reference to the king of the color of the actual player
    MKing* getKing();
    //return the squares the piece in x,y can move to, required to graphical assistance (highlight square by colour)
    vector<pair<int, int> > assist(int _x,int _y);
    //generate notation for a move
    void generateNotation(string _pieceName, int _x1, int _y1, int _x2, int _y2, bool _captured);
    //generate move from notation
    string moveFromNotation(Color _color, string _notation);
    //getter for notation
    string getNotation();
    //intermediate decoder used in moveFromNotation (translates coordinates to base 0 coordinates)
    string decode(string _name, string _promName, Color _color , string _conf, string _des);
    //try moving a piece (if exists) from x1,y1 to x2,y2
    bool play(int _x1,int _y1,int _x2,int _y2);
    //Manages capturing a piece
    void capture(int _x,int _y);
    //Promote a pawn to a selected piece (selected in GUI)
    void promote(int _x, int _y, string _piece_type);
    //return whether the game is at Mate
    bool isMate();
    //return whether the game is stuck by stalemate
    bool isStalemate();
    //return if a game is draw
    bool isDraw();
    //a particular case of draw
    bool insufficientMaterial();
    //a particular case of draw
    bool threeRepetition();

    //needed to detect three repetition and visualise games (back and forth)
    void saveState();

    //set the state at the beginning of the game
    void goToFirst();
    //set the state at the previous move (if exists)
    void goToPrevious();
    //set the state at the next move (if exists)
    void goToNext();
    //set the state at the last move played
    void goToLast();
    //determine if the state displayed is the last move played (to deny movement of pieces if otherwise)
    bool isLastState();

    //getter for a white non-captured piece
    MPiece* getWhitePiece(int _x);
    //getter for a black non-captured piece
    MPiece* getBlackPiece(int _x);
    //getter for a white captured piece
    MPiece* getWhiteCaptured(int _x);
    //getter for a black captured piece
    MPiece* getBlackCaptured(int _x);
    //getter for number of white captured pieces
    int getNumberWhiteCaptured();
    //getter for number of black captured pieces
    int getNumberBlackCaptured();

    //getter for the state visualized on the board
    int getStateNumber();
    //displays the board (for debug obviously)
    void debug();

private:

    Color turn;
    MPiece* board[8][8];
    bool cantPlay;
    MPiece* whitePieces[16];
    MPiece* blackPieces[16];
    MPiece* whiteCaptured[15];
    MPiece* blackCaptured[15];
    int numberWhiteCaptured;
    int numberBlackCaptured;
    string notation;
    int fiftyMove;
    int stateNumber;
    vector<MState> states;

};

#endif // GAME_H
