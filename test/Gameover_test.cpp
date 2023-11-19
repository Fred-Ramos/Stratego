#include "testfunctions.h"

#include <gtest/gtest.h>

TEST (Gameovertest, noflag){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[0][0] = new Flag('R');  //place red flag in position 0 0
    TestGame.mqGameBoard.mqpaaBoard[0][1] = new Scout('B'); //place blue scout in position 0 1

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Flag('B');  //place blue flag in position 9 0
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('R'); //place red scout in position 9 1


    ExpectedBoard.mqpaaBoard[0][0] = new Flag('R'); //Expected board
    ExpectedBoard.mqpaaBoard[0][1] = new Scout('B'); 

    ExpectedBoard.mqpaaBoard[9][0] = new Scout('R'); 
    ExpectedBoard.mqpaaBoard[9][1] = 0; 

    TestGame.GetNextMove(9, 1, 9, 0, TestGame.mqGameBoard.mqpaaBoard);                  //move red scout to the flag

    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    EXPECT_TRUE(TestGame.IsGameOver()); //game is over since flag is taken
    
    EXPECT_EQ('R',TestGame.winner);     //red player wins
}

TEST (Gameovertest, nomovingpieces){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[0][0] = new Flag('R');  //place red flag in position 0 0
    TestGame.mqGameBoard.mqpaaBoard[0][1] = new Scout('B'); //place blue scout in position 0 1

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Flag('B');  //place blue flag in position 9 0
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('R'); //place red scout in position 9 1


    ExpectedBoard.mqpaaBoard[0][0] = new Flag('R'); //Expected board
    ExpectedBoard.mqpaaBoard[0][1] = 0; 

    ExpectedBoard.mqpaaBoard[9][0] = new Flag('B'); 
    ExpectedBoard.mqpaaBoard[9][1] = 0; 

    TestGame.GetNextMove(9, 1, 0, 1, TestGame.mqGameBoard.mqpaaBoard);                  //move red scout to blue scout

    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    EXPECT_TRUE(TestGame.IsGameOver()); //game is over since no moving pieces left
    
    EXPECT_EQ('D',TestGame.winner);     //its a draw
}
