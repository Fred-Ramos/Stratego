#include <iostream>

#include "game.h"

int main() {
	Game qGame;    //create instance of the game

	do { //while game is not over
		qGame.Start(); //run the game
	} while (!qGame.IsGameOver());

	qGame.mqGameBoard.Print(); //print board when the game finishes
	
	using namespace std;
	cout << "GAME ENDED ";
	cout << endl;




	return 0;      //return 0(sucessfull) when game finishes
}