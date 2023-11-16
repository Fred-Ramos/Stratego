#include <iostream>

#include "board.h"

//BOARD CLASS
Board::Board() {                                          //board constructor
		for (int iRow = 0; iRow < 10; ++iRow) {         //for rows 0 to 9 (10rows)      
			for (int iCol = 0; iCol < 10; ++iCol) {     //for columns 0 to 9 (10columns)
				mqpaaBoard[iRow][iCol] = 0;            //piece is 0, all squares are empty
			}
		}

		//PLACE WATER(ALLWAYS PRESENT)
		mqpaaBoard[4][2] = new Water('G');
		mqpaaBoard[4][3] = new Water('G');
		mqpaaBoard[4][6] = new Water('G');
		mqpaaBoard[4][7] = new Water('G');
		mqpaaBoard[5][2] = new Water('G');
		mqpaaBoard[5][3] = new Water('G');
		mqpaaBoard[5][6] = new Water('G');
		mqpaaBoard[5][7] = new Water('G');

		//FILL FIRST 2 ROWS OF EACH SIDE(FOR TESTING)///////

		// Allocate and place blue pieces
		mqpaaBoard[8][0] = new Miner('B');
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
		mqpaaBoard[1][1] = new Miner('R');
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

Board::~Board() {                                      //desctructor
	for (int iRow = 0; iRow < 10; ++iRow) {        //for rows 0 to 9 (10rows)  
		for (int iCol = 0; iCol < 10; ++iCol) {    //for lines 0 to 9 (10rows)  
			delete mqpaaBoard[iRow][iCol];        //delete piece
			mqpaaBoard[iRow][iCol] = 0;           //pointer set to 0, to avoid bugs
		}
	}
}

void Board :: Print(){                           
    using namespace std;  
    for (int iRow = 0; iRow < 10; ++iRow) {             //there are 10 rows
        for (int iCol = 0; iCol < 2*10; ++iCol) {         //there are 10 columns
			int iSquareCol = iCol/2;                  //actual column index
			if (mqpaaBoard[9-iRow][iSquareCol] != 0){  //if not empty, display piece
				if ((iCol % 2) == 0){
					cout << mqpaaBoard[9-iRow][iSquareCol]->GetColor();   //print piece coulor
				}
				else{
					cout << mqpaaBoard[9-iRow][iSquareCol]->GetPiece();   //print piece rank 
				}
			}
			else { //if empty, put space
                cout << ' ';
            } 
        }
        cout << endl; //close line
    }
}

int Board :: ComparePiece(BoardPiece* SourcePiece, BoardPiece* EndPiece) {                      //TESTING check if rank of piece is higher
	if (EndPiece == 0){                  //if empty
		return 1;
	}
	char SourceRank = SourcePiece->GetPiece();
	char EndRank = EndPiece->GetPiece();
	if (isdigit(EndRank)){ //if is a ranked piece
		int S = SourceRank - '0'; //from ASCII  to 0<->9
		int E = EndRank - '0';

		if (S > E){
			return 1; //nothing changes, defending piece is deleted
		}
		else if (E > S){
			return -1; //atacking piece remains in place
		}
		else if(E == S){
			return 0; //defending piece is deleted, put atacking piece too
		}
	}
	return 1;
}
