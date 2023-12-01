#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include "piece.h"
#include <vector>
#include <iostream>
#include <ostream>

class Player{
	private:
	std::vector<Piece*> Pieces;
	int colour; // red = 1, blue  = 2
	bool isHuman;
	int wins = 0;
	bool has_flag;

	public:
	Player(std::string name, int colour, std::vector<Piece*>&Pieces, bool isHuman);
	~Player();
	bool makeMove(); // need to implement
	char getColour() const;
	std::vector<Piece*>* getPieces() const;
};

#endif