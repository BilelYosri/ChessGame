#ifndef GGAME_H
#define GGAME_H

#include "modelClasses/mgame.h"
#include "gpiece.h"
#include "modelClasses/mtimer.h"
#include "gsquare.h"
#include "gnotation.h"
#include <stack>

class GWindow;

class GGame
{
public:
    //Constructor
    GGame(GWindow* _parent, bool _hasTime, int _timeWhite, int _timeBlack, int _increment, bool _assist);
    ~GGame();

    //load game from a text file (.txt/.csv)
    void loadGame(QTextStream* in);
    //update pieces on the board
    void updatePieces();
    //initialise board's squares
    void initBoard();
    //used in assistance mode, highlight possible square the piece at x,y can go to
    void highlightMoves(int _x, int _y);
    //calls the model's play function and update the GUI accordingly
    bool play(int _x1, int _y1, int _x2, int _y2, string _prom);
    //adds a notation in the notations sections
    void addNotation(string _move);
    //reset squares highlight colors
    void resetAllSquares();
    //return a graphical aspect of a piece in x,y position
    GPiece* getPiece(int _x, int _y);
    //getter used in playing without drag and drop
    GPiece* getStartPiece();
    //setter used in playing without drag and drop
    void setStartPiece(GPiece* _piece);
    //Scroll has some strange behaviour in notations section, so we tweaked it with this method
    void updateScroll();
    //determine if a piece can move to a square
    void tryMove(QGraphicsSceneMouseEvent* _event);
    //generates the file content to be saved (called in save() method in GWindow)
    void generateSaveContent(QTextStream* _out);
    //highlight the notation at the actual game state
    void highlightNotation();

    //navigates to the first state of the game
    void goToFirst();
    //navigates to the previous state of the game
    void goToPrevious();
    //navigates to the next state of the game
    void goToNext();
    //navigates to the current state of the game (where you can play)
    void goToLast();

    //block game when time has ended
    void blockGame();

private:
    MGame* mGame;
    GWindow* parent;
    MTimer* whiteTimer;
    MTimer* blackTimer;
    QGraphicsScene* mainScene;
    QGraphicsScene* upperScene;
    QGraphicsScene* lowerScene;
    QGraphicsScene* notationScene;
    bool timeEnded;

    Square* squares[8][8];
    GPiece* pieces[32];
    GPiece* startPiece;
    //GNotation* notation;
    vector< GNotation* > notations;

    bool hasTime;
    int timeWhite;
    int timeBlack;
    int increment;
    bool assist;

    int whiteCaptured;
    int blackCaptured;
    int number;

    stack<QGraphicsPixmapItem*> lastCapturedWhite;
    stack<QGraphicsPixmapItem*> lastCapturedBlack;

    void initPieces();
    void initNotations();
    void switchClock(Color _color);
};

#endif // GGAME_H
