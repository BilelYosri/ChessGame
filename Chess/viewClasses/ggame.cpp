#include "ggame.h"
#include "gconstants.h"
#include "dialog_mate.h"
#include "dialog_draw.h"
#include "gwindow.h"

GGame::GGame(GWindow* _parent, bool _hasTime, int _timeWhite, int _timeBlack, int _increment, bool _assist)
{
    parent = _parent;
    hasTime = _hasTime;
    timeWhite = _timeWhite;
    timeBlack = _timeBlack;
    increment = _increment;
    assist = _assist;

    timeEnded = false;

    mainScene = _parent->getMainScene();
    upperScene = _parent->getUpperScene();
    lowerScene = _parent->getLowerScene();
    notationScene = _parent->getNotationScene();
    startPiece = nullptr;

    lastCapturedWhite;
    lastCapturedBlack;

    mGame = new MGame();
    whiteCaptured = blackCaptured = 0;
    number = 1;
    mGame->generatePossibleMoves();
    mGame->saveState();
    initBoard();
    for (int i=0; i<32; i++)
    {
        pieces[i] = nullptr;
    }
    initPieces();
    initNotations();
    if (hasTime)
    {
        parent->initTimers(timeWhite, timeBlack, increment);
        whiteTimer = _parent->getWhiteTimer();
        blackTimer = _parent->getBlackTimer();
    }
    else
    {
        parent->initTimers(0,0,0);
    }
    int min = parent->getMinScroll();
    parent->updateScroll(min,min);
}

GGame::~GGame()
{
    for (int i=0; i<32; i++)
        delete pieces[i];
    delete mGame;
}

void GGame::loadGame(QTextStream *in)
{
    QStringList fields;
    QStringList moveFields;
    QString line;
    int x1,x2,y1,y2;
    while( !(line = in->readLine()).isEmpty())
    {
        string move;
        fields = line.split(',');
        if (!(((QString) fields[0]).at(0).isDigit()))
        {
            move = mGame->moveFromNotation(white,((QString)fields[0]).toStdString());
            moveFields = QString::fromStdString(move).split(',');
            x1=((QString)moveFields.at(2)).toInt();
            y1=((QString)moveFields.at(3)).toInt();
            x2=((QString)moveFields.at(4)).toInt();
            y2=((QString)moveFields.at(5)).toInt();

            if (moveFields.at(0) == moveFields.at(1))
                play(x1,y1,x2,y2,"");
            else
                play(x1,y1,x2,y2,((QString)moveFields.at(1)).toStdString());

        }

        if ( !((QString)fields[1]).isEmpty())
        {
            if (!(((QString) fields[1]).at(0).isDigit()))
            {
                move = mGame->moveFromNotation(black,((QString)fields[1]).toStdString());
                moveFields = QString::fromStdString(move).split(',');
                x1=((QString)moveFields.at(2)).toInt();
                y1=((QString)moveFields.at(3)).toInt();
                x2=((QString)moveFields.at(4)).toInt();
                y2=((QString)moveFields.at(5)).toInt();
                if (moveFields.at(0) == moveFields.at(1))
                    play(x1,y1,x2,y2,"");
                else
                    play(x1,y1,x2,y2,((QString)moveFields.at(1)).toStdString());
            }
        }


    }
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
        if (pieces[i] != nullptr)
        {
            pieces[i]->updatePiece(mGame->getTurn());
            if ( (i==15) || (i==31) )
            {
                if ( ( (MKing*) ( pieces[i]->getModel() ) )->isInCheck() )
                {

                    int x = pieces[i]->getModel()->getX();
                    int y = pieces[i]->getModel()->getY();
                    squares[x][y]->highlight(redCheckColor);
                }
            }
            if (!mGame->isLastState())
                pieces[i]->setMovable(false);
        }
    }

    if (mGame->getNumberWhiteCaptured() > whiteCaptured)
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
        upperScene->addItem(item);
        lastCapturedWhite.push(item);
    }
    else if (mGame->getNumberWhiteCaptured() < whiteCaptured)
    {
        whiteCaptured = mGame->getNumberWhiteCaptured();
        upperScene->removeItem(lastCapturedWhite.top());
        lastCapturedWhite.pop();
    }

    if (mGame->getNumberBlackCaptured() > blackCaptured)
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
        lowerScene->addItem(item);
        lastCapturedBlack.push(item);
    }
    else if (mGame->getNumberBlackCaptured() < blackCaptured)
    {
        blackCaptured = mGame->getNumberBlackCaptured();
        lowerScene->removeItem(lastCapturedBlack.top());
        lastCapturedBlack.pop();
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
            mainScene->addItem(squares[i][j]);
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
        if ((vect.size() == 0) && assist)
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
            if (squares[_x][_y]->isDark())
                squares[_x][_y]->highlight(selectedDarkColor);
            else
                squares[_x][_y]->highlight(selectedLightColor);

        }
        if (assist)
        {
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
}

bool GGame::play(int _x1, int _y1, int _x2, int _y2, string _prom)
{
    bool captured = (mGame->getSquare(_x2,_y2) != nullptr);

    if (mGame->play(_x1, _y1, _x2, _y2))
    {
        MPiece* p = mGame->getSquare(_x2,_y2);
        int rank = p->getRank();

        if (p->getName() == "pawn")
        {
            Color color = p->getColor();
            if ((color == white) && (_y2 == 7))
            {
                mGame->promote(_x2,_y2, parent->promote(color,_prom));
                pieces[rank]->promote(mGame->getWhitePiece(rank));
            }
            else if ((color == black) && (_y2 == 0))
            {
                mGame->promote(_x2,_y2, parent->promote(color,_prom));
                pieces[16 + rank]->promote(mGame->getBlackPiece(rank));
            }
        }
        mGame->generatePossibleMoves();
        mGame->saveState();

        mGame->generateNotation(p->getName(), _x1, _y1,_x2, _y2, captured);

        resetAllSquares();
        updatePieces();
        if (hasTime)
            switchClock(mGame->getTurn());
        addNotation(mGame->getNotation());
        if (mGame->isMate())
        {
            if (hasTime)
            {
                parent->getBlackTimer()->pause();
                parent->getWhiteTimer()->pause();
            }
            notations[number-1]->endGame(mGame->getTurn(), true);

            DialogMate dialog(parent,parent);
            dialog.setModal(true);
            dialog.setBackground((Color) -(mGame->getTurn()));
            dialog.exec();
        }
        else if (mGame->isDraw())
        {
            blockGame();
            if (hasTime)
            {
                parent->getBlackTimer()->pause();
                parent->getWhiteTimer()->pause();
            }
            notations[number-1]->endGame(mGame->getTurn(), false);
            DialogDraw dialog(parent,parent);
            dialog.setModal(true);
            dialog.exec();
        }
        //mGame->debug();
        return true;
    }
    else
    {
        return false;
    }
}

void GGame::addNotation(string _move)
{
    GNotation* gNotation = notations[number-1];
    if (mGame->getTurn() == black)
    {
        gNotation->highlight(black);
        gNotation->setWhiteMove(_move);
    }
    else
    {
        gNotation->unhighlight();
        gNotation->setBlackMove(_move);
        if (number == notations.size())
        {
            GNotation* notation = new GNotation(this, number+1);
            notations.push_back(notation);
            notationScene->addItem(notation);
        }
        number++;
        notations[number-1]->highlight(white);
    }
    parent->scrollDown();
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

GPiece* GGame::getPiece(int _x, int _y)
{
    GPiece* p = nullptr;
    int i=0;
    while ((i<32) && (p == nullptr))
    {
        MPiece* model = pieces[i]->getModel();
        if ( (model->getX() == _x) && (model->getY() == _y) )
            p = pieces[i];
        i++;
    }

    return p;
}

GPiece *GGame::getStartPiece()
{
    return startPiece;
}

void GGame::setStartPiece(GPiece *_piece)
{
    startPiece = _piece;
}

void GGame::updateScroll()
{
    //parent->updateScroll(parent->ui);
}

void GGame::tryMove(QGraphicsSceneMouseEvent* _event)
{
    if (startPiece != nullptr)
    {
        int x1 = startPiece->getModel()->getX();
        int y1 = startPiece->getModel()->getY();
        QPointF pos = _event->scenePos();
        int x2 = fabs(pos.x() + 636/2) / 79.5;
        int y2 = fabs(pos.y() - 636/2) / 79.5;

        bool possible = play(x1, y1, x2, y2, "");
        if (possible)
        {
            startPiece->setScenePos(x2,y2);
            startPiece = nullptr;
        }
        else
            startPiece->setScenePos(x1,y1);
    }
}

void GGame::generateSaveContent(QTextStream *_out)
{
    int wt = 0;
    int bt = 0;
    if (hasTime)
    {
        wt = whiteTimer->getTime().hour()*3600 + whiteTimer->getTime().minute()*60 + whiteTimer->getTime().second();
        bt = blackTimer->getTime().hour()*3600 + blackTimer->getTime().minute()*60 + blackTimer->getTime().second();
    }

    if (timeEnded)
        wt = bt = 0;

    (*_out) << "hasTime," << ((hasTime)?'1':'0') << endl;
    (*_out) << "timeWhite," << wt << endl;
    (*_out) << "timeBlack," << bt << endl;
    (*_out) << "increment," << increment << endl;
    (*_out) << "assist," << ((assist)?'1':'0') << endl;
    for (int i=0; i<notations.size() && notations[i]->getWhiteMove()!="";i++)
    {
        GNotation* current = notations[i];
        (*_out) << QString::fromStdString(current->getWhiteMove()) << "," << QString::fromStdString(current->getBlackMove()) << '\n';
    }
}

void GGame::highlightNotation()
{
    for (int i=0; i<notations.size(); i++)
        notations[i]->unhighlight();
    int nb = mGame->getStateNumber();
    if (nb%2)
        notations[nb/2]->highlight(black);
    else
        notations[nb/2]->highlight(white);
}

void GGame::goToFirst()
{
    mGame->goToFirst();
    resetAllSquares();
    initPieces();
    updatePieces();
    highlightNotation();
    //mGame->debug();
}

void GGame::goToPrevious()
{
    mGame->goToPrevious();
    resetAllSquares();
    initPieces();
    updatePieces();
    highlightNotation();
    //mGame->debug();
}

void GGame::goToNext()
{
    mGame->goToNext();
    resetAllSquares();
    initPieces();
    updatePieces();
    highlightNotation();
    //mGame->debug();
}

void GGame::goToLast()
{
    mGame->goToLast();
    resetAllSquares();
    initPieces();
    updatePieces();
    highlightNotation();
    //mGame->debug();
}

void GGame::blockGame()
{
    for (int i=0; i<32; i++)
    {
        GPiece* p = pieces[i];
        if (p != nullptr)
        {
            p->setMovable(false);
        }
    }
    notations[number-1]->endGame(mGame->getTurn(), true);
    timeEnded = true;
}

void GGame::initPieces()
{
    for (int i=0; i<32; i++)
    {
        if (pieces[i] != nullptr)
            mainScene->removeItem(pieces[i]);
        pieces[i] = nullptr;
    }

    for (int i=0; i<16; i++)
    {
        MPiece* mp = mGame->getWhitePiece(i);
        if (mp != nullptr)
        {
            GPiece* gp = new GPiece(mp, this, mainScene);
            pieces[i] = gp;
        }
    }

    for (int i=0; i<16; i++)
    {
        MPiece* mp = mGame->getBlackPiece(i);
        if (mp != nullptr)
        {
            GPiece* gp = new GPiece(mp, this, mainScene);
            pieces[16+i] = gp;
        }
    }
}

void GGame::initNotations()
{
    notations.clear();
    notationScene->clear();
    for (int i=1; i<=9; i++)
    {
        GNotation* notation = new GNotation(this, i);
        notations.push_back(notation);
        notationScene->addItem(notation);
    }
    notations[0]->highlight(white);
}

void GGame::switchClock(Color _color)
{
    if (_color == white)
    {
        if (blackTimer->hasStarted())
        {
            blackTimer->pause();
            //parent->onTimeChanged(black, blackTimer->getTime());
        }
        whiteTimer->resume();
    }
    else
    {
        if (whiteTimer->hasStarted())
        {
            whiteTimer->pause();
            //parent->onTimeChanged(white, whiteTimer->getTime());
        }
        blackTimer->resume();
    }
}
