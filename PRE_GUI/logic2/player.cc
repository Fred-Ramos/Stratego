#include "player.h"
#include "board.h"
#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

Player :: Player(std::string name,int colour,vector<Piece*>&Pieces,bool isHuman): name(name), colour(colour), Pieces(Pieces), isHuman(isHuman)
{	
}

Player ::~Player(){
}

char Player :: getColour()const{
	return colour;
}
vector<Piece*>* Player::Pieces() const{
	return &Pieces;
}
bool Player :: makeMove(){
	
}
