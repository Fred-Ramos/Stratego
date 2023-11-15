#include <iostream>

class BoardPiece
{
public:
	BoardPiece(char cColor) : mcColor(cColor) {}   //constructor of the class, 1 argument only, colour cColor; initializes mcColor as cColor
	~BoardPiece() {}                               //destructor of the class
	virtual char GetPiece() = 0;                   //declare GetPiece function         
	char GetColor() {                              //call Piece's colour
		return mcColor;
	}
	bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {    //function that determines if the move is legal (true or false)
		BoardPiece* qpDest = qpaaBoard[iDestRow][iDestCol];                            //piece that occupies the board at destiny coordinates
		if (qpDest->GetPiece() == 'W'){ //if moving to water, move is ilegal
			return false;
		}
		else if ((qpDest == 0) || (mcColor != qpDest->GetColor())) {                       //if destiny square is empty or destiny piece is of diferent colour of moving piece
			return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);  //arguments: source row, source column, destiny row, destiny column, game board   ; function that checks, for each piece type, possible legalmoves
		}
		else{
			return false;                                                            //if destiny square has a piece of same colour, is allways a illegal move
		}
	}
private:
	virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) = 0; //declares AreSquarelegal function
	char mcColor;                                                                                                     //store the colour of the piece privatly (cant be changed)
};

//WATER, unmovable, no piece can move here
class Water : public BoardPiece  
{
public:
	Water(char cColor) : BoardPiece(cColor) {}   //constructor
	~Water() {}
private:
	virtual char GetPiece() {   //return 2, type of piece 2, SCOUT
		return 'W';
	}


	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
		return false; //is immovable
	}
	
};

//SCOUT, can move any number of squares in a straight line
class Scout : public BoardPiece  
{
public:
	Scout(char cColor) : BoardPiece(cColor) {}   //constructor
	~Scout() {}
private:
	virtual char GetPiece() {   //return 2, type of piece 2, SCOUT
		return '2';
	}


	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
		if (iSrcRow == iDestRow) { //if moving in a column
			// Make sure that all invervening squares are empty
			int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;   //1 if increasing in column, -1 if decreasing in column 
			for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {  //check column trajectory
				if (qpaaBoard[iSrcRow][iCheckCol] != 0) {  //check squares are empty (cannot go over pieces)
					return false;                          //if not empty, illegal move
				}
			}
			return true;                                   //if all empty, legal move
		} 
		else if (iDestCol == iSrcCol) {  //if moving in a row         
			// Make sure that all invervening squares are empty
			int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1; //1 if increasing in row, -1 if decreasing in row
			for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) { //check row trajectory
				if (qpaaBoard[iCheckRow][iSrcCol] != 0) { //check squares are empty (cannot go over pieces)
					return false;                         //if not empty, illegal move
				}
			} 
			return true;                                  //if all empty, legal move
		}
		return false; //if not moving in straight line, move is illegal
	}
};

//Miner, moves 1 square in 1 direction, can disarm BOMBS
class Miner : public BoardPiece  
{
public:
	Miner(char cColor) : BoardPiece(cColor) {}   //constructor
	~Miner() {}
private:
	virtual char GetPiece() {   //return 2, type of piece 2, SCOUT
		return '3';
	}


	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
		if (iSrcRow == iDestRow) { //if moving in a column
			if ( abs(iSrcCol - iDestCol) == 1 ){ //if moving 1 square exactly
				return true;
			}
		}
		else if (iDestCol == iSrcCol) {  //if moving in a row
			if ( abs(iSrcRow - iDestRow) == 1 ){ //if moving 1 square exactly
				return true;
			}
		}
		return false; //if not moving 1 square horizontally or vertically, move is illegal
	}
};



class Board
{
public:
BoardPiece* mqpaaBoard[10][10];
	Board() {                                          //board constructor
		for (int iRow = 0; iRow < 10; ++iRow) {         //for rows 0 to 9 (10rows)      
			for (int iCol = 0; iCol < 10; ++iCol) {     //for columns 0 to 9 (10columns)
				mqpaaBoard[iRow][iCol] = 0;            //piece is 0, all squares are empty
			}
		}

		//FILL FIRST 2 ROWS OF EACH SIDE(FOR TESTING)///////

		//PLACE WATER(ALLWAYS PRESENT)
		mqpaaBoard[4][2] = new Scout('B');
		mqpaaBoard[4][3] = new Scout('B');
		mqpaaBoard[8][2] = new Scout('B');
		mqpaaBoard[8][3] = new Scout('B');
		mqpaaBoard[8][4] = new Scout('B');
		mqpaaBoard[8][5] = new Scout('B');
		mqpaaBoard[8][6] = new Scout('B');
		mqpaaBoard[8][7] = new Scout('B');


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
	~Board() {                                        //desctructor
		for (int iRow = 0; iRow < 10; ++iRow) {        //for rows 0 to 8 (10rows)  
			for (int iCol = 0; iCol < 10; ++iCol) {    //for lines 0 to 8 (10rows)  
				delete mqpaaBoard[iRow][iCol];        //delete piece
				mqpaaBoard[iRow][iCol] = 0;           //pointer set to 0, to avoid bugs
			}
		}
	}

	//PRINT THE GAME BOARD, FOR TESTING, LATER INPLEMENT GRAPHICAL INTERFACE
	void Print() {                           
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

	bool ComparePiece() {                      //TESTING check if rank of piece is higher
		return true;
	}
};

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

	void GetNextMove(BoardPiece* qpaaBoard[10][10]) {  //current boar as the input
		using namespace std;
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
				BoardPiece* qpStartPiece = qpaaBoard[iStartRow][iStartCol]; //pointer to current piece to move
				if ((qpStartPiece != 0) && (qpStartPiece->GetColor() == mcPlayerTurn)) { //if piece is the correct color
					if (qpStartPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard)) { // if destination is a valid destination

						// Make the move
						BoardPiece* qpEndPiece					= qpaaBoard[iEndRow][iEndCol];        //store end position
						qpaaBoard[iEndRow][iEndCol]		=     qpaaBoard[iStartRow][iStartCol];    //change end position to start position
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

int main() {
	Game qGame;    //create instance of the game
	qGame.Start(); //start the game
	return 0;      //return 0(sucessfull) when game finishes
}