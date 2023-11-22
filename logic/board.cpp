#include <iostream>

#include "board.h"


//BOARD CLASS
Board::Board() {                                          //board constructor
	using namespace std;
		for (int iRow = 0; iRow < 10; ++iRow) {           //for rows 0 to 9 (10rows)      
			for (int iCol = 0; iCol < 10; ++iCol) {       //for columns 0 to 9 (10columns)
				mqpaaBoard[iRow][iCol] = 0;               //piece is 0, all squares are empty
			}
		}
		
		//PLACE WATER(ALLWAYS PRESENT)

		//mqpaaBoard[4][2] = new Water('G');
		//mqpaaBoard[4][3] = new Water('G');
		//mqpaaBoard[4][6] = new Water('G');
		//mqpaaBoard[4][7] = new Water('G');
		//mqpaaBoard[5][2] = new Water('G');
		//mqpaaBoard[5][3] = new Water('G');
		//mqpaaBoard[5][6] = new Water('G');
		//mqpaaBoard[5][7] = new Water('G');
		
		for(int iRow = 4; iRow < 6; ++iRow){
			for(int iCol : {2, 3, 6, 7}){
				mqpaaBoard[iRow][iCol] = new Water('G');
			}
		}

		//FILL FIRST 2 ROWS OF EACH SIDE(FOR TESTING)///////

		// Allocate and place blue pieces (iRow from 8 - 9)

		for(int bluepiece = 0; bluepiece < 20; ++bluepiece){
			Print();
			int iStartMove;
			cout << "Blue Square: ";
			cin >> iStartMove;
			int iStartRow = (iStartMove / 10);
        	int iStartCol = (iStartMove % 10);
			cout << "Piece?";
			char piece;
			cin >> piece;
			
			if( (7 < iStartRow ) && ( iStartRow < 10) ){
				switch(piece){

					case 'F':

					mqpaaBoard[iStartRow][iStartCol] = new Flag('B');
					break;

					case 'B':
					mqpaaBoard[iStartRow][iStartCol] = new Bomb('B');
					break;

					case '0':
					mqpaaBoard[iStartRow][iStartCol] = new Spy('B');
					break;

					case '1':
					mqpaaBoard[iStartRow][iStartCol] = new Scout('B');
					break;

					case '2':
					mqpaaBoard[iStartRow][iStartCol] = new Miner('B');
					break;

					case '3':
					mqpaaBoard[iStartRow][iStartCol] = new Sergeant('B');
					break;

					case '4':
					mqpaaBoard[iStartRow][iStartCol] = new Lieutenant('B');
					break;

					case '5':
					mqpaaBoard[iStartRow][iStartCol] = new Captain('B');
					break;

					case '6':
					mqpaaBoard[iStartRow][iStartCol] = new Major('B');
					break;

					case '7':
					mqpaaBoard[iStartRow][iStartCol] = new Colonel('B');
					break;

					case '8':
					mqpaaBoard[iStartRow][iStartCol] = new General('B');
					break;

					case '9':
					mqpaaBoard[iStartRow][iStartCol] = new Marshal('B');
					break;
				}
			}
			else{
				cout << "Invalid move!" << endl;
			}
		}


		//mqpaaBoard[8][0] = new Scout('B');
		//mqpaaBoard[8][1] = new Miner('B');
		//mqpaaBoard[8][2] = new Bomb('B');
		//mqpaaBoard[8][3] = new Sergeant('B');
		//mqpaaBoard[8][4] = new Lieutenant('B');
		//mqpaaBoard[8][5] = new Captain('B');
		//mqpaaBoard[8][6] = new Major('B');
		//mqpaaBoard[8][7] = new Colonel('B');
		//mqpaaBoard[8][8] = new General('B');
		//mqpaaBoard[8][9] = new Marshal('B');

		//mqpaaBoard[9][0] = new Flag('B');
		//mqpaaBoard[9][1] = new Scout('B');
		//mqpaaBoard[9][2] = new Scout('B');
		//mqpaaBoard[9][3] = new Scout('B');
		//mqpaaBoard[9][4] = new Scout('B');
		//mqpaaBoard[9][5] = new Scout('B');
		//mqpaaBoard[9][6] = new Scout('B');
		//mqpaaBoard[9][7] = new Scout('B');
		//mqpaaBoard[9][8] = new Scout('B');
		//mqpaaBoard[9][9] = new Scout('B');

		// Allocate and place red pieces (iRow from 0 - 1)

		for(int redpiece = 0; redpiece < 20; ++redpiece){
			Print();
			int iStartMove;
			cout << "Red Square: ";
			cin >> iStartMove;
			int iStartRow = (iStartMove / 10);
        	int iStartCol = (iStartMove % 10);
			cout << "Piece?";
			char piece;
			cin >> piece;
			
			if( (0 < iStartRow ) && ( iStartRow < 2) ){
				switch(piece){

					case 'F':
					mqpaaBoard[iStartRow][iStartCol] = new Flag('R');
					break;

					case 'B':
					mqpaaBoard[iStartRow][iStartCol] = new Bomb('R');
					break;

					case '0':
					mqpaaBoard[iStartRow][iStartCol] = new Spy('R');
					break;

					case '1':
					mqpaaBoard[iStartRow][iStartCol] = new Scout('R');
					break;

					case '2':
					mqpaaBoard[iStartRow][iStartCol] = new Miner('R');
					break;

					case '3':
					mqpaaBoard[iStartRow][iStartCol] = new Sergeant('R');
					break;

					case '4':
					mqpaaBoard[iStartRow][iStartCol] = new Lieutenant('R');
					break;

					case '5':
					mqpaaBoard[iStartRow][iStartCol] = new Captain('R');
					break;

					case '6':
					mqpaaBoard[iStartRow][iStartCol] = new Major('R');
					break;

					case '7':
					mqpaaBoard[iStartRow][iStartCol] = new Colonel('R');
					break;

					case '8':
					mqpaaBoard[iStartRow][iStartCol] = new General('R');
					break;

					case '9':
					mqpaaBoard[iStartRow][iStartCol] = new Marshal('R');
					break;
				}
			}
			else{
				cout << "Invalid move!" << endl;
			}
		}


		//mqpaaBoard[1][0] = new Bomb('R');
		//mqpaaBoard[1][1] = new Miner('R');
		//mqpaaBoard[1][2] = new Flag('R');
		//mqpaaBoard[1][3] = new Scout('R');
		//mqpaaBoard[1][4] = new Scout('R');
		//mqpaaBoard[1][5] = new Scout('R');
		//mqpaaBoard[1][6] = new Scout('R');
		//mqpaaBoard[1][7] = new Scout('R');
		//mqpaaBoard[1][8] = new Scout('R');
		//mqpaaBoard[1][9] = new Scout('R');

		//mqpaaBoard[0][0] = new Scout('R');
		//mqpaaBoard[0][1] = new Scout('R');
		//mqpaaBoard[0][2] = new Scout('R');
		//mqpaaBoard[0][3] = new Scout('R');
		//mqpaaBoard[0][4] = new Scout('R');
		//mqpaaBoard[0][5] = new Scout('R');
		//mqpaaBoard[0][6] = new Scout('R');
		//mqpaaBoard[0][7] = new Scout('R');
		//mqpaaBoard[0][8] = new Scout('R');
		//mqpaaBoard[0][9] = new Spy('R');
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
	cout << endl; 
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

//Compare function, returns: 0(both pieces die), 1(atacking piece wins), -1(defending piece wins)
int Board :: ComparePiece(BoardPiece* SourcePiece, BoardPiece* EndPiece) {                      // check if rank of piece is higher
	if (EndPiece == 0){                  //if empty
		return 1;
	}
	char SourceRank = SourcePiece->GetPiece();
	char EndRank = EndPiece->GetPiece();
	if (isdigit(EndRank)){ //if is a ranked piece(is a number)
		int S = SourceRank - '0'; //from ASCII  to 0<->9
		int E = EndRank - '0';

		if ((S == 0) && (E == 9)){ //if spy is atacking and marshal defending, spy wins(only exception to rank rule)
			return 1; //nothing changes, defending piece is deleted
		}
		else if (S > E){
			return 1; //nothing changes, defending piece is deleted
		}
		else if (E > S){
			return -1; //atacking piece remains in place
		}
		else if(E == S){
			return 0; //defending piece is deleted, put atacking piece too
		}
	}
	if (EndRank == 'B'){
		if (SourceRank == '2'){
			return 1; //Miner disarms bomb, bomb piece looses
		}
		else{
			return 0; //Bomb explodes, both pieces loose
		}
	}
	return 1;
}

int Board :: Legalmovesleft() {
	bool red_movable = false;
	bool blue_movable = false;
	bool red_flag = false;
	bool blue_flag = false;
	//TESTING check if flag is taken or if any player has movable pieces left
    for (int i = 0; i < 10; ++i) { //run all lines
        for (int j = 0; j < 10; ++j) { //run all columns
            if (mqpaaBoard[i][j] != 0){ //if piece not empty
				BoardPiece* rbpiece = mqpaaBoard[i][j]; //save piece
				char rbtype = rbpiece->GetPiece();
				if (rbtype == 'F'){                                    //if it is a flag
					if (rbpiece->GetColor() == 'R'){ //if it is a red flag
						red_flag = true;
					}
					else{                            //else it is a blue flag
						blue_flag = true;
					}
				}
                else if ( (rbtype != 'W') || (rbtype != 'B')){ //if piece is not water, a flag or a bomb
					if (rbpiece->GetColor() == 'R'){           //if it is a movable red piece
						red_movable = true;       
					} 
					else{                                     //else it is a movable blue piece
						blue_movable = true;
					}
                }
            }
        }
    }
	if ( (red_flag == true) && (blue_flag == false)){ //if only red flag present, blue has no legal moves left and looses
		return 1;
	}
	else if ( (red_flag == false) && (blue_flag == true)){ //if only blue flag present, red has no legal moves left and looses
		return -1;
	}
	else if ( (red_movable == true) && (blue_movable) == false){ //if only red has movable pieces left, blue has no legal moves left and looses
		return 1;
	}
	else if ( (red_movable == false) && (blue_movable == true) ){ //if only blue has movable pieces left, red has no legal moves left and looses
		return -1;
	}
	else if ( (red_movable == false) && (blue_movable == false) ){ //if by chance the last 2 movable pieces kill each other, leaving no movable pieces for none of the players, the game is a draw
		return -2; 
	}
	return 0; //if none of the above, then both have legal moves left
}


