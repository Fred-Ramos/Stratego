#include "piece.h"
#include "board.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Board mqGameBoard;  //Store board 
	Game() : mcPlayerTurn('R') {}   //constructor; initializes mcPlayerturn as "R"
	~Game() {}                      //destructor; does nothing

	void Run(); //Run Game

	void GetNextMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]);  //current boar as the input

	void AlternateTurn(); //change player turn

	bool IsGameOver(); //check if game is over
	
	char winner = 0;        //which player wins
private:
	bool Validmove = false; //initially, set valid move as false
	char mcPlayerTurn;  //store player turn as private
};

#endif