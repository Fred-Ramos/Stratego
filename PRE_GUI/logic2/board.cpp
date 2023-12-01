#include <iostream>
#include "piece.h"
#include "board.h"

class Board
{
    public:
    Piece* mqpaaBoard[10][10];
	Board() {                                          //board constructor
	for (int iRow = 0; iRow < 10; ++iRow) {         //for rows 0 to 9 (10rows)      
	    for (int iCol = 0; iCol < 10; ++iCol) {     //for columns 0 to 9 (10columns)
		    mqpaaBoard[iRow][iCol] = 0;            //piece is 0, all squares are empty
	    }
	}

	//FILL FIRST 2 ROWS OF EACH SIDE(FOR TESTING)///////

	// Allocate and place blue pieces
	mqpaaBoard[8][0] = new Scout('B');
	mqpaaBoard[8][1] = new Scout('B');
	mqpaaBoard[8][2] = new Scout('B');
	mqpaaBoard[8][3] = new Scout('B');
	mqpaaBoard[8][4] = new Scout('B');
	mqpaaBoard[8][5] = new Scout('B');
	mqpaaBoard[8][6] = new Scout('B');
	mqpaaBoard[8][7] = new Scout('B');
	mqpaaBoard[8][8] = new Scout('B');
	mqpaaBoard[8][9] = new Scout('B');
	mqpaaBoard[9][0] = new Scout('B');
	mqpaaBoard[9][1] = new Scout('B');
	mqpaaBoard[9][2] = new Scout('B');
	mqpaaBoard[9][3] = new Scout('B');
	mqpaaBoard[9][4] = new Scout('B');
	mqpaaBoard[9][5] = new Scout('B');
	mqpaaBoard[9][6] = new Scout('B');
	mqpaaBoard[9][7] = new Scout('B');
	mqpaaBoard[9][8] = new Scout('B');
	mqpaaBoard[9][9] = new Scout('B');
	// Allocate and place red pieces
	mqpaaBoard[1][0] = new Scout('R');
	mqpaaBoard[1][1] = new Scout('R');
	mqpaaBoard[1][2] = new Scout('R');
	mqpaaBoard[1][3] = new Scout('R');
	mqpaaBoard[1][4] = new Scout('R');
	mqpaaBoard[1][5] = new Scout('R');
	mqpaaBoard[1][6] = new Scout('R');
	mqpaaBoard[1][7] = new Scout('R');
	mqpaaBoard[1][8] = new Scout('R');
	mqpaaBoard[1][9] = new Scout('R');
	mqpaaBoard[0][0] = new Scout('R');
	mqpaaBoard[0][1] = new Scout('R');
	mqpaaBoard[0][2] = new Scout('R');
	mqpaaBoard[0][3] = new Scout('R');
	mqpaaBoard[0][4] = new Scout('R');
	mqpaaBoard[0][5] = new Scout('R');
	mqpaaBoard[0][6] = new Scout('R');
    mqpaaBoard[0][7] = new Scout('R');
	mqpaaBoard[0][8] = new Scout('R');
	mqpaaBoard[0][9] = new Scout('R');
	}

	~Board() {                                        //desctructor
	    for (int iRow = 0; iRow < 10; ++iRow) {        //for rows 0 to 8 (10rows)  
		    for (int iCol = 0; iCol < 10; ++iCol) {    //for lines 0 to 8 (10rows)  
			    delete mqpaaBoard[iRow][iCol];        //delete piece
			    mqpaaBoard[iRow][iCol] = 0;           //pointer set to 0, to avoid bugs
		    }
	    }
	}
}