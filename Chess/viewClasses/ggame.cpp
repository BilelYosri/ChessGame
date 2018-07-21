#include "ggame.h"
#include "gconstants.h"

GGame::GGame(QGraphicsScene* _scene,  QGraphicsScene* _whiteCapturedScene,  QGraphicsScene* _blackCapturedScene)
{
    scene = _scene;
    whiteCapturedScene = _whiteCapturedScene;
    blackCapturedScene = _blackCapturedScene;
    MPlayer p1,p2;
    mGame = new MGame(0,p1,p2);
    whiteCaptured = blackCaptured = 0;
    mGame->generatePossibleMoves();
    initBoard();
    initPieces();
}

GGame::~GGame()
{
    for (int i=0; i<32; i++)
        delete pieces[i];
    delete mGame;
}

void GGame::updatePieces()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            squares[i][j]->uncheck();
        }
    }
    for (int i=0; i<32; i++)
    {
        pieces[i]->updatePiece(mGame->getTurn());
        if (i==15 || i==31)
        {
            if ( ( (MKing*) ( pieces[i]->getModel() ) )->isInCheck() )
            {

                int x = pieces[i]->getModel()->getX();
                int y = pieces[i]->getModel()->getY();
                squares[x][y]->highlight(redCheckColor);
            }
        }
    }
    if (mGame->getNumberWhiteCaptured() != whiteCaptured)
    {
        whiteCaptured = mGame->getNumberWhiteCaptured();
        MPiece* p = mGame->getWhiteCaptured(whiteCaptured-1);
        QString file = QString(":img/res/black_%1.png").arg(QString::fromStdString(p->getName()));
        QPixmap img = QPixmap(file);
        img = img.scaledToHeight(25, Qt::SmoothTransformation);
        int width = 20;//img.width();
        int height = img.height();
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(img);
        item->setPos((whiteCaptured)*width*1.5,0);
        whiteCapturedScene->addItem(item);
    }

    if (mGame->getNumberBlackCaptured() != blackCaptured)
    {
        blackCaptured = mGame->getNumberBlackCaptured();
        MPiece* p = mGame->getBlackCaptured(blackCaptured-1);
        QString file = QString(":img/res/white_%1.png").arg(QString::fromStdString(p->getName()));
        QPixmap img = QPixmap(file);
        img = img.scaledToHeight(25, Qt::SmoothTransformation);
        int width = 22;
        int height = img.height();
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(img);
        item->setPos((blackCaptured)*width*1.5,0);
        blackCapturedScene->addItem(item);
    }
}

void GGame::initBoard()
{
    bool isDark = true;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (isDark)
                squares[i][j] = new Square(this,isDark,i,j);
            else
                squares[i][j] = new Square(this,isDark,i,j);
            scene->addItem(squares[i][j]);
            isDark = !isDark;
        }
        isDark = !isDark;
    }
}

void GGame::highlightMoves(int _x, int _y)
{
    MPiece* p = mGame->getSquare(_x,_y);
    if (p!=nullptr && p->getColor() == mGame->getTurn())
    {
        if (!squares[_x][_y]->isColored())
        {
            resetAllSquares();
        }
        vector<pair<int, int> > vect = mGame->assist(_x,_y);
        if (vect.size() == 0)
        {
            if (!squares[_x][_y]->isColored())
            {
                if (squares[_x][_y]->isDark())
                    squares[_x][_y]->highlight(redDarkColor);
                else
                    squares[_x][_y]->highlight(redLightColor);
            }
            else
                squares[_x][_y]->resetColor();
        }
        else
        {
            squares[_x][_y]->highlight(greenCurrentColor);
        }
        for (pair<int, int> pr : vect)
        {
            QColor colHigh;
            int a = pr.first;
            int b = pr.second;

            if (squares[a][b]->isDark())
                colHigh = greenDarkColor;
            else
                colHigh = greenLightColor;

            if (!squares[a][b]->isColored())
                squares[a][b]->highlight(colHigh);

            else
            {
                squares[a][b]->resetColor();
                squares[_x][_y]->resetColor();
            }
        }
    }
}

bool GGame::play(int _x1, int _y1, int _x2, int _y2)
{
    if (mGame->play(_x1, _y1, _x2, _y2))
    {
        resetAllSquares();
        updatePieces();
        return true;
    }
    else
    {

        return false;
    }
}

void GGame::resetAllSquares()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            squares[i][j]->resetColor();
        }
    }
}

void GGame::initPieces()
{
    for (int i=0; i<16; i++)
    {
        MPiece* mp = mGame->getWhitePiece(i);
        if (mp != nullptr)
        {
            GPiece* gp = new GPiece(mp, this, scene);
            pieces[i] = gp;
        }
    }

    for (int i=0; i<16; i++)
    {
        MPiece* mp = mGame->getBlackPiece(i);
        if (mp != nullptr)
        {
            GPiece* gp = new GPiece(mp, this, scene);
            pieces[16+i] = gp;
        }
    }
}
