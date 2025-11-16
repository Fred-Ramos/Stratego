#include "../src/game.h"

void CleanTestBoard(BoardPiece* qpaaBoard[10][10]){
    //clean board(for now because board constructor fills it up with a demo)
    //when SETUPBOARDPIECES function created, change this part:
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            qpaaBoard[i][j] = 0;
        }
    }
    /////
}

//compare 2 boards
bool CompareBoards(BoardPiece* qpaaBoard1[10][10], BoardPiece* qpaaBoard2[10][10]){
	for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if ( (qpaaBoard1[i][j] == 0) || (qpaaBoard2[i][j] == 0) ){       //if position is empty in one of the boards
				if (qpaaBoard1[i][j] != qpaaBoard2[i][j]){                   //it should also be for the other board
					return false;
				}
			}
			else{                                                            //if position not empty in neither of the boards
				if ( (qpaaBoard1[i][j]->GetPiece() != qpaaBoard2[i][j]->GetPiece()) || (qpaaBoard1[i][j]->GetColor() != qpaaBoard2[i][j]->GetColor()) ){ //then it must be the same piecetype and color
					return false;
				}
			}
        }
    }
	return true;
}