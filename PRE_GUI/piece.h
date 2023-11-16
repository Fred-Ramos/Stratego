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
	virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]); //declares AreSquarelegal function
	
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

//BOMB, doesnt move, if engaged kills any troop, except for the Miner
class Bomb : public BoardPiece  
{
public:
	Bomb(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Bomb() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

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

};

//Sergeant, moves 1 square in 1 direction
class Sergeant : public BoardPiece  
{
public:
	Sergeant(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Sergeant() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//Lieutenant, moves 1 square in 1 direction
class Lieutenant : public BoardPiece  
{
public:
	Lieutenant(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Lieutenant() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//Captain, moves 1 square in 1 direction
class Captain : public BoardPiece  
{
public:
	Captain(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Captain() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//Major, moves 1 square in 1 direction
class Major : public BoardPiece  
{
public:
	Major(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Major() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//Colonel, moves 1 square in 1 direction
class Colonel : public BoardPiece  
{
public:
	Colonel(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Colonel() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//General, moves 1 square in 1 direction
class General : public BoardPiece  
{
public:
	General(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~General() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

//Marshal, moves 1 square in 1 direction
class Marshal : public BoardPiece  
{
public:
	Marshal(char cColor) : BoardPiece(cColor) {}   //constructor
	virtual ~Marshal() {}                                  //destructor

private:
	char GetPiece();  //return "rank" of piece, "3"

};

#endif