#include "gsquare.h"
#include "ggame.h"
#include "gconstants.h"

Square::Square(GGame* _gGame, bool _dark, int _x, int _y)
{
    gGame = _gGame;
    dark = _dark;
    resetColor();
    x = _x;
    y = _y;
    setFlag(ItemIsMovable, true);
}

QRectF Square::boundingRect() const
{
    float a = x * SIDE - 318;
    float b = 318 - (y * SIDE) - SIDE;
    return QRectF(a, b, SIDE, SIDE);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(color);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    QString s = QString("%1,%2").arg(char(x+'A')).arg(y+1);
}

void Square::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    GPiece* p = gGame->getPiece(x,y);
    if (p != nullptr)
    {
        p->mouseMoveEvent(event);
    }

}

void Square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    GPiece* p = gGame->getPiece(x,y);
    if (p != nullptr)
    {
        p->mouseReleaseEvent(event);
    }
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GPiece* p = gGame->getPiece(x,y);
    if (p != nullptr)
    {
        p->mousePressEvent(event);
    }
    else
    {
        gGame->tryMove(event);
    }
}

void Square::highlight(QColor _color)
{
    if (color != redCheckColor || _color != greenCurrentColor)
    {

        colored = !colored;
        color = _color;
        update();
    }

}

void Square::resetColor()
{
    if (color != redCheckColor)
    {
        if (dark)
            color = darkColor;
        else
            color = lightColor;
        update();
        colored = false;
    }
}

void Square::uncheck()
{
    if (color == redCheckColor)
        if (dark)
            color = darkColor;
        else
            color = lightColor;
        update();
        colored = false;
}

bool Square::isDark()
{
    return dark;
}

bool Square::isColored()
{
    return colored;
}
