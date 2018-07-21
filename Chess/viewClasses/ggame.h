#ifndef GGAME_H
#define GGAME_H

#include "modelClasses/mgame.h"
#include "gpiece.h"
#include "gsquare.h"

class GGame
{
public:
    GGame(QGraphicsScene* _scene, QGraphicsScene* _whiteCapturedScene, QGraphicsScene* _blackCapturedScene );
    ~GGame();

    void updatePieces();
    void initBoard();
    void highlightMoves(int _x, int _y);
    bool play(int _x1, int _y1, int _x2, int _y2);
    void resetAllSquares();

private:
    MGame* mGame;
    QGraphicsScene* scene;
    QGraphicsScene* whiteCapturedScene;
    QGraphicsScene* blackCapturedScene;
    Square* squares[8][8];
    GPiece* pieces[32];
    int whiteCaptured;
    int blackCaptured;

    void initPieces();
};

#endif // GGAME_H
