#include <iostream>

#ifndef PIECE_H
#define PIECE_H

class BoardPiece
{
public:
	BoardPiece(char cColor) : mcColor(cColor) {}   //constructor of the class, 1 argument only, colour cColor; initializes mcColor as cColor
	virtual ~BoardPiece() {}                               //destructor of the class

	virtual char GetPiece() = 0;                   //declare GetPiece function 

	char GetColor();                            //call Piece's colour
	
	bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]);  //function that determines if the move is legal (true or false)

private:
	virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) = 0; //declares AreSquarelegal function
	
	char mcColor;                                                                                                          //store the colour of the piece privatly (cant be changed)
};

//WATER, unmovable, no piece can move here
class Water : public BoardPiece  
{
public:
	Water(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Water() {}                                  //destructor

private:
	virtual char GetPiece();   //return piece's rank, "W"

	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]);
};

//SCOUT, can move any number of squares in a straight line
class Scout : public BoardPiece  
{
public:
	Scout(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Scout() {}                                  //destructor

private:
	char GetPiece(); //return "rank" of piece, "2"

	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]);
};

//MINER, moves 1 square in 1 direction, can disarm BOMBS
class Miner : public BoardPiece  
{
public:
	Miner(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Miner() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]);
};

#endif