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
		mqpaaBoard[4][2] = new Water('B');
		mqpaaBoard[4][3] = new Water('B');
		mqpaaBoard[4][6] = new Water('B');
		mqpaaBoard[4][7] = new Water('B');
		mqpaaBoard[5][2] = new Water('B');
		mqpaaBoard[5][3] = new Water('B');
		mqpaaBoard[5][6] = new Water('B');
		mqpaaBoard[5][7] = new Water('B');

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
    const int kiSquareWidth = 4;                                      //square width
    const int kiSquareHeight = 3;                                     //square height
    for (int iRow = 0; iRow < 10*kiSquareHeight; ++iRow) {             //there are 10 rows, each row has height kiSquareHeight
        int iSquareRow = iRow/kiSquareHeight;                         //so that iSquareRow increase by 1 each 3iRow (true index)
        // PRINT SIDE BORDER WITH NUMBERING
        if (iRow % kiSquareHeight == 1) {                             //if row in middle of Square, display row number
            cout << '-' << (char)('9' - iSquareRow ) << '-';
        } 
        else {                                                        //else make row "divider"
            cout << "---";
        }
        // PRINT GAME BOARD
        for (int iCol = 0; iCol < 10*kiSquareWidth; ++iCol) {         //there are 10 columns, each column has width kiSquareWidth
            int iSquareCol = iCol/kiSquareWidth;                     //so that iSquareCol increase by 1 each 4iCol (true index)
            if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && mqpaaBoard[9-iSquareRow][iSquareCol] != 0) {  //if in center of Square and board square not empty
                if ((iCol % 4) == 1) {    //if line in middle of Square
                    cout << mqpaaBoard[9-iSquareRow][iSquareCol]->GetColor();   //print piece coulor 
                } 
                else {
                    cout << mqpaaBoard[9-iSquareRow][iSquareCol]->GetPiece();   //print piece rank 
                }
            } 
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    // PRINT BOTTOM BORDER WITH NUMBERING
    for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {          ////1 row of height kiSquareHeight below the "board"
        if (iRow % 3 == 1) {
            cout << "---";                                       //start line by filling first Square row with "-"
            for (int iCol = 0; iCol < 10*kiSquareWidth; ++iCol) { //there are 10 columns, each column has width kiSquareWidth
                int iSquareCol = iCol/kiSquareWidth;             //so that iSquareCol increase by 1 each 4iCol (true index)
                if ((iCol % 4) == 1) {                           //if row in "middle" of Square
                    cout << (iSquareCol);                        //display column number
                }                                                
                else {
                    cout << '-';                                 //else make column "divider"
                }
            }
            cout << endl;                                        //finish line
        } 
        else {
            for (int iCol = 1; iCol < 11*kiSquareWidth; ++iCol) { //else make "divider" between numbering and edge of board and board
                cout << '-';                                     //all columns filled with "-"
            }
            cout << endl;                                        //finish line
        }
    }
}

bool Board :: ComparePiece(){                      //TESTING check if rank of piece is higher
    return true;
}