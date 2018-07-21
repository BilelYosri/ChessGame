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
    GPiece(MPiece* _behavior,GGame* _gGame, QGraphicsScene* _scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    MPiece* getModel();
    void updatePiece(Color);
    void setMovable(bool _movable);
    void addToScene();
    int getSceneX();
    int getSceneY();
    void setScenePos(int _x, int _y);

protected:
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
