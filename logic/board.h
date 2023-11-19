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

	//0(both have legalmoves), 1(only red has legal moves), -1(only blue has legal moves)
	int Legalmovesleft(); //which player(color) has legal moves left
};

#endif