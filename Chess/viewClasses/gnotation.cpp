#include "gnotation.h"
#include "gconstants.h"
#include "ggame.h"

GNotation::GNotation(GGame *_gGame, int _number):
    whiteBrush(whitishColor), blackBrush(whitishColor)
{
    gGame = _gGame;
    number = _number;
    x = -sceneWidth/2;
    y = -sceneHeight/2 + height*(number-1);
    whiteMoved = blackMoved = false;
}

QRectF GNotation::boundingRect() const
{
    return QRectF(x, y, sceneWidth - 2, height - 2);
}

void GNotation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(whitishColor);
    painter->fillRect(rec,brush);

    float recWidth = separatorDistance - numberWidth;
    QRectF miniWhiteRec (x + numberWidth, y, recWidth, numberHeight);
    painter->fillRect(miniWhiteRec,whiteBrush);
    QRectF miniBlackRec (x + separatorDistance, y, recWidth, numberHeight);
    painter->fillRect(miniBlackRec,blackBrush);

    QPen pen(Qt::black, 2);
    QPen penLine(Qt::black, 3);
    painter->setPen(pen);
    painter->drawRect(rec);
    painter->setPen(penLine);
    QLineF numberLine (x + numberWidth, y, x + numberWidth, y+numberHeight);
    QLineF separatorLine (x + separatorDistance, y, x + separatorDistance, y+numberHeight);
    painter->drawLine(numberLine);
    painter->drawLine(separatorLine);

    QFont font("Bahnschrift");
    font.setPointSize(18);
    painter->setFont(font);
    painter->drawText(x+3, y+3, sceneWidth - 5, height - 5, 0, QString::number(number));

    //painter->drawText(x+30, y+3, sceneWidth - 5, height - 5, 0, "Qc4xe6+");

    if (whiteMoved)
        painter->drawText(x + numberWidth+12, y+3, sceneWidth - 5, height - 5, 0, QString::fromStdString(whiteMove));

    if (blackMoved)
        painter->drawText(x + separatorDistance+12, y+3,  sceneWidth - 5, height - 5, 0, QString::fromStdString(blackMove));
}



void GNotation::setWhiteMove(string _move)
{
    whiteMove = _move;
    whiteMoved = true;
    update();
}

void GNotation::setBlackMove(string _move)
{
    blackMove = _move;
    blackMoved = true;
    update();
}

void GNotation::highlight(Color _color)
{
    if (_color == white)
    {
        whiteBrush.setColor(blueishColor);
        blackBrush.setColor(whitishColor);
    }
    else
    {
        blackBrush.setColor(blueishColor);
        whiteBrush.setColor(whitishColor);
    }
    update();
}

void GNotation::endGame(Color _color, bool _isMate)
{
    if (_color == white)
    {
        whiteBrush.setColor(reddishColor);
        blackBrush.setColor(whitishColor);
        whiteMoved = true;
        if (_isMate)
            whiteMove = "0 - 1";
        else
            whiteMove = "1/2 - 1/2";
    }
    else
    {
        whiteBrush.setColor(whitishColor);
        blackBrush.setColor(reddishColor);
        blackMoved = true;
        if (_isMate)
            blackMove = "1 - 0";
        else
            blackMove = "1/2 - 1/2";
    }
    update();
}

void GNotation::unhighlight()
{
    whiteBrush.setColor(whitishColor);
    blackBrush.setColor(whitishColor);
    update();
}

string GNotation::getWhiteMove()
{
    return whiteMove;
}

string GNotation::getBlackMove()
{
    return blackMove;
}
