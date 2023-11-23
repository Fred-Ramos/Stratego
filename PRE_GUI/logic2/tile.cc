#include "tile.h"
#include "piece.h"
#include <iostream>


Tile :: Tile(int x, int y): x(x), y(y), Active(NULL)
{
}
Tile :: Tile(){
}
Tile :: ~Tile(){
}
void Tile :: setPiece(Piece * p){
	Active = p;
}
bool Tile :: isEmpty()const{
	return (Active == NULL);
}
Piece* Tile ::  getActive()const{
	return Active;
}
int Tile ::  getX()const{
	return x;
}
int  Tile :: getY()const{
	return y;
}
void Tile :: display(){
	if(isEmpty()){
		Active->display();
		return;
	}
	if(x == 4 || x == 5){
		 if(y == 2 || y == 3 || y == 6 || y == 7){	
			std::cout << "~~~";
			return;
		 }
	}
	std::cout << " - ";
	
}
