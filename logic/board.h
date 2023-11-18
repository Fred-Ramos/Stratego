#include "piece.h"

#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
BoardPiece* mqpaaBoard[10][10];
	Board();  //constructor
	virtual ~Board(); //destructor

	//PRINT THE GAME BOARD, FOR TESTING, LATER INPLEMENT GRAPHICAL INTERFACE
	void Print();

	int ComparePiece(BoardPiece* SourcePiece, BoardPiece* EndPiece);                     //TESTING check if rank of piece is higher
};

#endif