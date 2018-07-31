#ifndef GPIECE_H
#define GPIECE_H

#include <string>
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "modelClasses/mpiece.h"

using namespace std;

class GGame;

class GPiece: public QGraphicsPixmapItem
{
public:
    //Constructor
    GPiece(MPiece* _model,GGame* _gGame, QGraphicsScene* _scene);
    //Destructor
    ~GPiece();
    //Mouse Events used to move a piece around whenever possible
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //get the logical equivalent piece on the model game (logical piece)
    MPiece* getModel();
    //updates piece on the board (coordinates change, or captured, or promoted)
    void updatePiece(Color);
    //used to block or allow piece movement
    void setMovable(bool _movable);
    //determine whether we can move a piece
    bool getMovable();
    //displays the piece on board
    void addToScene();
    //gets the coordinates of the scene (not the board: can be negative since the center is 0,0)
    int getSceneX();
    int getSceneY();
    //sets the position on the scene
    void setScenePos(int _x, int _y);
    //remove the piece from board
    void removeFromScene();
    //sets the equivalent model game's piece
    void setModel(MPiece* _model);
    //sets a new model for the graphical pawn when the promotion piece is selected
    void promote(MPiece*);

protected:
    bool isAlive;
    bool isMovable;

    float width;
    float height;
    int sceneX;
    int sceneY;
    int pressX;
    int pressY;
    string png;
    MPiece* model;
    GGame* gGame;
    QGraphicsScene* scene;
    QPixmap img;


    const float SIDE_SQUARE = 79.5;
    const float SIDE_SCENE = 636 ;
};

#endif // GPIECE_H
