#include "gpiece.h"
#include "ggame.h"

GPiece::GPiece(MPiece* _model,GGame* _gGame, QGraphicsScene *_scene):
    model(_model), gGame(_gGame), scene(_scene)
{
    isAlive = true;
    setModel(_model);
    updatePiece(white);
    addToScene();
}

GPiece::~GPiece()
{
    //scene->removeItem(this);
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
        setZValue(0);
        QPointF pos = event->scenePos();
        int x2 = min((fabs(pos.x() + SIDE_SCENE/2) / SIDE_SQUARE),7.0);
        if (x2<0)
            x2 = 0;
        int y2 = min((fabs(pos.y() - SIDE_SCENE/2) / SIDE_SQUARE),7.0);
        if (y2<0)
            y2 = 0;

        bool possible = gGame->play(x1, y1, x2, y2, "");
        if (possible)
        {
            setScenePos(x2,y2);
            gGame->setStartPiece(nullptr);
        }

        else
            setScenePos(x1,y1);
    }
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
    if (isMovable)
    {
        setZValue(1);
        gGame->highlightMoves(model->getX(), model->getY());
        gGame->setStartPiece(this);
    }
    else
    {
        gGame->tryMove(event);
        setZValue(0);
    }
}

MPiece *GPiece::getModel()
{
    return model;
}

void GPiece::updatePiece(Color _turn)
{
    setMovable( ( ( _turn) == (model->getColor()) ) );
    int x = model->getX();
    int y = model->getY();
    if (x>=0)
    {
        setScenePos(x,y);
    }
    else
    {
        if (isAlive)
        {
            scene->removeItem(this);
            isAlive = false;
        }
    }
}

void GPiece::setMovable(bool _movable)
{
    isMovable = _movable;
    setFlag(ItemIsMovable, _movable);
}

bool GPiece::getMovable()
{
    return isMovable;
}

void GPiece::addToScene()
{
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

void GPiece::removeFromScene()
{
    scene->removeItem(this);
}

void GPiece::setModel(MPiece* _model)
{
    model = _model;
    QString col = "white";
    if (model->getColor() == black)
        col = "black";
    QString file = QString(":img/res/%1_%2.png").arg(col).arg(QString::fromStdString(model->getName()));
    img = QPixmap(file);
    img = img.scaledToHeight(55, Qt::SmoothTransformation);
    width = img.width();
    height = img.height();
    setPixmap(img);
}

void GPiece::promote(MPiece* _newModel)
{
    setModel(_newModel);
}
