#include <iostream>
#include "game.h"
#include "piece.h"
using namespace std;

class Game
{
public:
	Game() : mcPlayerTurn('R') {}   //constructor; initializes mcPlayerturn as "R"
	~Game() {}                      //destructor; does nothing

	void Start() {
		do { //while game is not over
			GetNextMove(mqGameBoard.mqpaaBoard);     //get input for next move 
			AlternateTurn();                         //alternate turn
		} while (!IsGameOver());
		mqGameBoard.Print();       //print board when the game finishes
	}

	void GetNextMove(Piece* qpaaBoard[10][10]) {  //current board as the input
		bool bValidMove		= false;   //initially, set valid move as false
		do {                           //while no valid move has been given:
			mqGameBoard.Print();

			// Get input and convert to coordinates
			cout << mcPlayerTurn << "'s Move: ";      //Print player colour for this turn
			int iStartMove;
			cin >> iStartMove;                        //input StartMove(piece to move)
			int iStartRow = (iStartMove / 10);    //transform RC(ROW COLUMN) into R
			int iStartCol = (iStartMove % 10);    //transform RC(ROW COLUMN) into C

			cout << "To: ";                           //"where to"
			int iEndMove;
			cin >> iEndMove;                          //input iEndMove (destination square)
			int iEndRow = (iEndMove / 10);        //transform RC(ROW COLUMN) into R
			int iEndCol = (iEndMove % 10);        //transform RC(ROW COLUMN) into C

			// Check that the indices are in range
			if ((iStartRow >= 0 && iStartRow < 10) && (iStartCol >= 0 && iStartCol < 10) && (iEndRow >= 0 && iEndRow < 10) && (iEndCol >= 0 && iEndCol < 10)) {
				// ADDITIONAL CHECKS IN HERE:
				Piece* qpStartPiece = qpaaBoard[iStartRow][iStartCol]; //pointer to current piece to move
				if ((qpStartPiece != 0) && (qpStartPiece->GetColor() == mcPlayerTurn)) { //if piece is the correct color
					if (qpStartPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard)) { // if destination is a valid destination

						// Make the move
						BoardPiece* qpEndPiece = qpaaBoard[iEndRow][iEndCol];        //store end position
						qpaaBoard[iEndRow][iEndCol] = qpaaBoard[iStartRow][iStartCol];    //change end position to start position
						qpaaBoard[iStartRow][iStartCol]	= 0;                                      //start position back to 0
						// TESTING CHECK RANKS TO SEE WHICH PIECE SURVIVES
						if (true) {   //if rank is HIGHER delete memory of endposition piece 
							delete qpEndPiece;
						} 
						else { // else keep endposition piece
							qpaaBoard[iEndRow][iEndCol]		= qpEndPiece;
						}
						bValidMove = true;
					}
				}
			}
			if (!bValidMove) {
				cout << "Invalid Move!" << endl;
			}
		} while (!bValidMove);
	}

	void AlternateTurn() {
		mcPlayerTurn = (mcPlayerTurn == 'R') ? 'B' : 'R';  //if RED finished, change to BLUE; else change to RED
	}

	bool IsGameOver() {
		//TESTING check if flag is taken or if any player has movable pieces left
		return false;
	}
private:
	Board mqGameBoard;  //Store board as private
	char mcPlayerTurn;  //store player turn as private
};