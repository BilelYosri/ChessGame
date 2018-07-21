#ifndef PIECE_H
#define PIECE_H

#include "mconstants.h"
#include <string>
#include <vector>
using namespace std;

class MGame;

class MPiece
{
protected:
    MGame* game;
    Color color;
    int x,y;
    int rank;
    bool possibilities[8][8];
    string name;

public:
    MPiece(MGame* _game, string _name, Color _color, int _x, int _y, int _rank);
    virtual bool generatePossibilities()=0;
    bool isPossible(int, int);
    virtual void move(int, int)=0;
    int getX();
    void setX(int _x);
    int getY();
    void setY(int _y);
    int getRank();
    string getName();
    Color getColor();
    vector< pair<int,int> > getPossibilities();
};

#endif // PIECE_H
