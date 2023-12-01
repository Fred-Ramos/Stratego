#ifndef __GAME__
#define __GAME__

#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include "piece.h"
#include "board.h"

class Game{
	private:
	Board mqGameBoard;  //Store board as private
	char mcPlayerTurn;  //store player turn as private

	public:
	Game();
    ~Game();
    void Start();
    void GetNextMove(Piece* qpaaBoard[10][10]);
    void AlternateTurn();
    bool IsGameOver();

};

#endif