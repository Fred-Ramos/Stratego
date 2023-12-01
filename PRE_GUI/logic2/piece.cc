#include "piece.h"
#include "player.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

Piece :: Piece(int colour, int type): colour(colour), type(type){
	isVisible = false;
}
Piece :: ~Piece(){
}
char Piece :: getColour() const{
	return colour;
}
Tile* Piece :: getLocation(){
	return location;
}
void Piece :: setLocation(Tile*){
	
}
//Almost all the stratego pieces move 1 unit in either forward
//backward, left or right.
//So only overriding required is for Bomb,Flag and Scout(which is only constrained by the board).
bool Piece :: getVisibility(){
	return isVisible;
}
void Piece :: setVisibility(bool f){
	isVisible = f;
}
void Piece::display(){
	
	if(colour == 1){
		cout << "\033[1;41m" << "RED TEAM";
	}else{
		cout << "\033[1;44m" << "BLUE TEAM";
	}

	switch(type){

		case BOMB:cout<<" B ";
		break;

		case MARSHAL:cout<<"MAR";
		break;

		case GENERAL:cout<<"GEN";
		break;

		case COLONEL:cout<<"COL";
		break;

		case MAJOR:cout<<"MAJ";
		break;

		case CAPTAIN:cout<<"CAP";
		break;

		case LIEUTENANT:cout<<"LIE";
		break;

		case SERGEANT:cout<<"SER";
		break;

		case SAPPER:cout<<"SAP";
		break;

		case SCOUT:cout<<"SCO";
		break;

		case SPY:cout<<"SPY";
		break;

		case FLAG:cout<<" F ";
		break;
	}
	cout << "\033[0m"; // Reset attributes to default
}

vector<Tile> Piece ::move(Tile board[][],int x, int y){
	possibleDestinations.clear();
	switch(type){
	case BOMB:
	case FLAG:
		return possibleDestinations;
	// No possible moves at any time for The bomb and the flag
	}
	int potX[4] = {x, x, x+1, x-1};
	int potY[4] = {y+1, y-1, y, y};

	//enumerate throught the four possible moves
	//The board is a [10][10] Tile matrix
	//possible ranges are [0-9][0-9]
	//with the exclusion of the water tiles
	//which are 2 2x2 sqaures in the middle of the field
	
	for(int i = 0; i < 4; ++i){
	 if(potX[i] >=0 && potX < 10){ // review logic
	  if(potY[i] >=0 && potY < 10){	//review logic
	//Destination is on the board
	   if(board[potX[i]][potY[i]] != NULL && board[potX[i]][potY[i]]->getPiece.getColour() != colour){
	    //Destination has enemy piece
	          //TODO:Prevent addition on water tiles
		if(potX[i] == 4 || potX[i] == 5){
		 if(potY[i] == 2 || potY[i] == 3 || potY[i] == 6 || potY[i] == 7){
		}else{
			possibleDestinations.add(board[potX[i]][potX[i]]);
		}
	       }
	 possibleDestinations.add(board[potX[i]][potY[i]]);
	   }
	  }
	 }
	}

	return possibleDestinations;
}


