#include "mpiece.h"
#include "mgame.h"

MPiece::MPiece(MGame* _game, string _name, Color _color, int _x, int _y, int _rank)
{
    name = _name;
    game = _game;
    color=_color;
    x=_x;
    y=_y;
    rank = _rank;
}

int MPiece::getX()
{
    return x;
}

void MPiece::setX(int _x)
{
    x=_x;
}

int MPiece::getY()
{
    return y;
}

void MPiece::setY(int _y)
{
    y=_y;
}

int MPiece::getRank()
{
    return rank;
}

string MPiece::getName()
{
    return name;
}

Color MPiece::getColor()
{
    return color;
}

vector<pair<int, int> > MPiece::getPossibilities()
{
    vector<pair<int, int> > vect;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (possibilities[i][j])
                vect.push_back(make_pair(i,j));
        }
    }
    return vect;
}

bool MPiece::isPossible(int _x, int _y)
{
    return possibilities[_x][_y];
}
