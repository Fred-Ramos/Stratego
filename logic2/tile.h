#ifndef __TILE_H__
#define __TILE_H__

#include <ostream>
#include <iostream>
#include "piece.h"
#include <string>
#include <vector>

class Tile{
	private:
	int x;
	int y;
	Piece* Active;
	
	public:
	Tile();
	Tile(int x, int y);
	~Tile();
	void setPiece(Piece * p); // for initializing game board
	bool isEmpty()const;
	Piece* getActive()const; // after moves have been made, aka works as getPiece() ?
	int getX()const;
	int getY()const;
	void display();
};
#endif
// Piece* board[10][10]={};

