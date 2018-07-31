#ifndef GNOTATION_H
#define GNOTATION_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <string>
#include "modelClasses/mconstants.h"
using namespace std;

class GGame;

class GNotation : public QGraphicsItem
{

public:
    //Constructor
    GNotation(GGame* _gGame, int _number);
    //inherited from QGraphicsItem: needed to determine the box the object occupies
    QRectF boundingRect() const;
    //inherited from QGraphicsItem: basically draws the object on the scene
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    //set the notation of the white move
    void setWhiteMove(string _move);
    //set the notation of the black move
    void setBlackMove(string _move);
    //Highlights the notation of the current state's move
    void highlight (Color _color);
    //generates score
    void endGame(Color _color, bool _isMate);
    //used to change the highlighted notation
    void unhighlight();
    //used in generate save file
    string getWhiteMove();
    //used in generate save file
    string getBlackMove();

private:
    GGame* gGame;
    int number;
    float x;
    float y;
    bool whiteMoved;
    bool blackMoved;
    string whiteMove;
    string blackMove;
    QBrush whiteBrush;
    QBrush blackBrush;
    const float height = 33.5635 ;
    const float numberWidth = 32.426;
    const float numberHeight = 34.006;
    const float separatorDistance = 136.957;
    const float sceneWidth = 241.488 ;
    const float sceneHeight = 341.143;
};

#endif // GNOTATION_H
