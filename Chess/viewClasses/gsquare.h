#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <QGraphicsItem>
#include <QPainter>

using namespace std;

class GGame;

class Square : public QGraphicsItem
{
public:
    //Constructor
    Square(GGame* _gGame, bool _dark, int _x, int _y);
    //inherited from QGraphicsItem: needed to determine the box the object occupies
    QRectF boundingRect() const;
    //inherited from QGraphicsItem: draws the square on the scene
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    //Mouse events Handlers
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //Highlight a square with a given color
    void highlight(QColor);
    //Resets the square to its original color
    void resetColor();
    //removes red highlight (equivalent to square's piece being in check)
    void uncheck();
    //determine if the square is dark or light one (black/white)
    bool isDark();
    //determine if a square is highlighted
    bool isColored();

private:
    GGame* gGame;
    QColor color;
    bool dark;
    bool colored;
    int x,y;

    const float SIDE = 79.5;


};

#endif // SQUARE_H
