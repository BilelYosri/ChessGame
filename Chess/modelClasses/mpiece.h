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
    //Set A Matrix representation of board of possible destination the piece can move to
    //All Pieces have to implement it (Pure Polymorphism)
    virtual bool generatePossibilities()=0;
    //determine if the piece can move to the given square
    bool isPossible(int, int);
    //move piece to the given square (only called when possible)
    //All Pieces have to implement it (Pure Polymorphism)
    virtual void move(int, int)=0;
    //get X Coordinate of the current position
    int getX();
    //set X Coordinate of the current position
    void setX(int _x);
    //get Y Coordinate of the current position
    int getY();
    //set Y Coordinate of the current position
    void setY(int _y);
    //get piece position in whitePieces/blackPieces array
    int getRank();
    //useful in generating the visual aspect (shape) of the piece
    string getName();
    //return the color of the piece
    Color getColor();
    //return a vecotr of possible moves (used in assistance)
    vector< pair<int,int> > getPossibilities();
};

#endif // PIECE_H
