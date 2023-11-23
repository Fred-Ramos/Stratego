#include <cstdlib> //its included in iostream

#include "piece.h"

//SIMPLE PIECE

bool BoardPiece :: IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]){    //function that determines if the move is legal (true or false)
    BoardPiece* qpDest = qpaaBoard[iDestRow][iDestCol];                            //piece that occupies the board at destiny coordinates

    if (qpDest !=0){ //if destiny square not empty
        if (qpDest->GetPiece() == 'W'){ //if destiny is water, move is ilegal
            return false;
        }
    }

    if ((qpDest == 0) || (mcColor != qpDest->GetColor())) {                       //if destiny square is empty or destiny piece is of diferent colour of moving piece
        return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);  //arguments: source row, source column, destiny row, destiny column, game board   ; function that checks, for each piece type, possible legalmoves
    }
    return false;                                                            //if destiny square has a piece of same colour, is allways a illegal move
}

char BoardPiece :: GetColor(){                              //call Piece's colour
	return mcColor;
}

bool BoardPiece :: AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {  //general movement(all moving pieces except scout)
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

//WATER PIECE
char Water :: GetPiece(){                              //call Piece's "rank"
	return 'W';
}

bool Water :: AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
    return false; //is immovable
}

//FLAG PIECE
char Flag :: GetPiece(){                              //call Piece's "rank"
	return 'F';
}

bool Flag :: AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
    return false; //is immovable
}


//BOMB PIECE
char Bomb :: GetPiece(){                              //call Piece's "rank"
    return 'B';
}

bool Bomb :: AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
    return false; //is immovable
}

//SPY PIECE
char Spy :: GetPiece(){                              //call Piece's "rank"
	return '0';
}

//SCOUT PIECE
char Scout :: GetPiece(){                              //call Piece's "rank"
	return '1';
}

bool Scout :: AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {
    if ((iSrcRow == iDestRow) ) { //if moving in a column and destiny is not water
        // Make sure that all invervening squares are empty
        int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;   //1 if increasing in column, -1 if decreasing in column 
        for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {  //check column trajectory
            if (qpaaBoard[iSrcRow][iCheckCol] != 0) {  //check squares are empty (cannot go over pieces)
                return false;                          //if not empty, illegal move
            }
        }
        return true;                                   //if all empty, legal move
    } 
    else if ((iDestCol == iSrcCol) ) {  //if moving in a row and destiny is not water        
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

//MINER PIECE
char Miner :: GetPiece(){                                //call Piece's "rank"
    return '2';
}

//SERGEANT PIECE
char Sergeant :: GetPiece(){                             //call Piece's "rank"
    return '3';
}

//LIEUTENANT PIECE
char Lieutenant :: GetPiece(){                          //call Piece's "rank"
    return '4';
}

//CAPTAIN PIECE
char Captain :: GetPiece(){                             //call Piece's "rank"
    return '5';
}

//MAJOR PIECE
char Major :: GetPiece(){                               //call Piece's "rank"
    return '6';
}

//COLONEL PIECE
char Colonel :: GetPiece(){                            //call Piece's "rank"
    return '7';
}

//GENERAL PIECE
char General :: GetPiece(){                            //call Piece's "rank"
    return '8';
}

//MARSHAL PIECE
char Marshal :: GetPiece(){                            //call Piece's "rank"
    return '9';
}