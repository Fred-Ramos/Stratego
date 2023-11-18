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

	void Start(); //Start Game

	void GetNextMove(BoardPiece* qpaaBoard[10][10]);  //current boar as the input

	void AlternateTurn(); //change player turn

	bool IsGameOver(); //check if game is over
private:
	char mcPlayerTurn;  //store player turn as private
};

#endif