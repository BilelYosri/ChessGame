#include "gpiece.h"
#include "ggame.h"

GPiece::GPiece(MPiece* _behavior,GGame* _gGame, QGraphicsScene *_scene):
    model(_behavior), gGame(_gGame), scene(_scene)
{

    QString col = "white";
    if (model->getColor() == black)
        col = "black";
    QString file = QString(":img/res/%1_%2.png").arg(col).arg(QString::fromStdString(model->getName()));
    img = QPixmap(file);
    img = img.scaledToHeight(55, Qt::SmoothTransformation);
    width = img.width();
    height = img.height();
    updatePiece(white);
    addToScene();
}

void GPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isMovable)
    {
        QPointF pos = event->scenePos();
        float nx = pos.x() - width/2;
        float ny = pos.y() - height/2;
        float wLeftBorder = -(SIDE_SCENE/2);
        float wRightBorder = (SIDE_SCENE/2) - width;
        float hTopBorder = -(SIDE_SCENE/2);
        float hBottomBorder = (SIDE_SCENE/2) - height;

        if (nx < wLeftBorder)
            nx = wLeftBorder;
        if (nx > wRightBorder)
            nx = wRightBorder;

        if (ny < hTopBorder)
            ny = hTopBorder;
        if (ny > hBottomBorder)
            ny = hBottomBorder;

        this->setPos(nx, ny);
    }
}

void GPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (isMovable)
    {
        int x1 = pressX;
        int y1 = pressY;

        QPointF pos = event->scenePos();
        int x2 = fabs(pos.x() + SIDE_SCENE/2) / SIDE_SQUARE;
        int y2 = fabs(pos.y() - SIDE_SCENE/2) / SIDE_SQUARE;

        bool possible = gGame->play(x1, y1, x2, y2);
        if (possible)
            setScenePos(x2,y2);
        else
            setScenePos(x1,y1);
    }
}

void GPiece::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (isMovable)
        gGame->highlightMoves(model->getX(), model->getY());
}

void GPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    pressX = fabs(pos.x() + SIDE_SCENE/2) / SIDE_SQUARE;
    pressY = fabs(pos.y() - SIDE_SCENE/2) / SIDE_SQUARE;
    if (!isMovable)
    {
        setScenePos(pressX, pressY);
    }
}

MPiece *GPiece::getModel()
{
    return model;
}

void GPiece::updatePiece(Color _turn)
{
    setMovable( ( _turn == model->getColor() ) );
    int x = model->getX();
    int y = model->getY();
    if (x!=-1)
        setScenePos(x,y);
    else
    {
        qDebug() << QString::fromStdString(model->getName()) << " Captured!";
        ///TODO: Change this later to add it to captured pieces
        scene->removeItem(this);
    }
}

void GPiece::setMovable(bool _movable)
{
    isMovable = _movable;
    setFlag(ItemIsMovable, _movable);
}

void GPiece::addToScene()
{
    this->setPixmap(img);
    setScenePos(model->getX(), model->getY());
    scene->addItem(this);
}

int GPiece::getSceneX()
{
    return sceneX;
}

int GPiece::getSceneY()
{
    return sceneY;
}

void GPiece::setScenePos(int _x, int _y)
{
    sceneX = _x;
    sceneY = _y;
    float x = _x * SIDE_SQUARE - 318 + SIDE_SQUARE/2 - width/2;
    float y = 318 - (_y * SIDE_SQUARE) - SIDE_SQUARE + SIDE_SQUARE/2 - height/2;
    this->setPos(x, y);
}
