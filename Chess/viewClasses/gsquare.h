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
    Square(GGame* _gGame, bool _dark, int _x, int _y);
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void highlight(QColor);
    void resetColor();
    void uncheck();
    bool isDark();
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
