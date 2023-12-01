#include "testfunctions.h"

#include <gtest/gtest.h>

TEST (Gameovertest, noBlueflag){

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

TEST (Gameovertest, noRedflag){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[0][0] = new Flag('R');  //place red flag in position 0 0
    TestGame.mqGameBoard.mqpaaBoard[0][1] = new Scout('B'); //place blue scout in position 0 1

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Flag('B');  //place blue flag in position 9 0
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('R'); //place red scout in position 9 1


    ExpectedBoard.mqpaaBoard[0][0] = new Scout('B'); //Expected board
    ExpectedBoard.mqpaaBoard[0][1] = 0; 

    ExpectedBoard.mqpaaBoard[9][0] = new Flag('B');
    ExpectedBoard.mqpaaBoard[9][1] = new Scout('R'); 

    TestGame.AlternateTurn();                                                           //change to blue player turn
    TestGame.GetNextMove(0, 1, 0, 0, TestGame.mqGameBoard.mqpaaBoard);                  //move blue scout to the flag

    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    EXPECT_TRUE(TestGame.IsGameOver()); //game is over since flag is taken
    
    EXPECT_EQ('B',TestGame.winner);     //blue player wins
}

TEST (Gameovertest, noRedBluemovingpieces){

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

TEST (Gameovertest, noBluemovingpieces){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[0][0] = new Flag('R');  //place red flag in position 0 0
    TestGame.mqGameBoard.mqpaaBoard[0][1] = new Scout('B'); //place blue scout in position 0 1
    TestGame.mqGameBoard.mqpaaBoard[0][2] = new Miner('R'); //place red miner in position 0 2

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Flag('B');  //place blue flag in position 9 0
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('R'); //place red scout in position 9 1


    ExpectedBoard.mqpaaBoard[0][0] = new Flag('R'); //Expected board
    ExpectedBoard.mqpaaBoard[0][1] = new Miner('R');
    ExpectedBoard.mqpaaBoard[0][2] = 0;

    ExpectedBoard.mqpaaBoard[9][0] = new Flag('B'); 
    ExpectedBoard.mqpaaBoard[9][1] = new Scout('R');

    TestGame.GetNextMove(0, 2, 0, 1, TestGame.mqGameBoard.mqpaaBoard);                  //move red miner to blue scout

    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    EXPECT_TRUE(TestGame.IsGameOver()); //game is over since no moving pieces left
    
    EXPECT_EQ('R',TestGame.winner);     //Red wins
}

TEST (Gameovertest, noRedmovingpieces){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[0][0] = new Flag('R');  //place red flag in position 0 0
    TestGame.mqGameBoard.mqpaaBoard[0][1] = new Scout('B'); //place blue scout in position 0 1

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Flag('B');  //place blue flag in position 9 0
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('R'); //place red scout in position 9 1
    TestGame.mqGameBoard.mqpaaBoard[9][2] = new Miner('B'); //place blue miner in position 9 2


    ExpectedBoard.mqpaaBoard[0][0] = new Flag('R'); //Expected board
    ExpectedBoard.mqpaaBoard[0][1] = new Scout('B');

    ExpectedBoard.mqpaaBoard[9][0] = new Flag('B'); 
    ExpectedBoard.mqpaaBoard[9][1] = new Miner('B');
    ExpectedBoard.mqpaaBoard[9][2] = 0;

    TestGame.AlternateTurn();                                                           //change to blue player turn
    TestGame.GetNextMove(9, 2, 9, 1, TestGame.mqGameBoard.mqpaaBoard);                  //move blue miner to red scout

    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    EXPECT_TRUE(TestGame.IsGameOver()); //game is over since no moving pieces left
    
    EXPECT_EQ('B',TestGame.winner);     //Blue wins
}
