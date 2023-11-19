#include "testfunctions.h"

#include <gtest/gtest.h>

TEST (Scouttest, simplemovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 5 5

    ExpectedBoard.mqpaaBoard[5][6] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(5, 5, 5, 6, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to the right
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][6] = 0;

    ExpectedBoard.mqpaaBoard[4][6] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(5, 6, 4, 6, TestGame.mqGameBoard.mqpaaBoard);                       //move scout down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[4][6] = 0;

    ExpectedBoard.mqpaaBoard[4][5] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(4, 6, 4, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to left
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[4][5] = 0;

    ExpectedBoard.mqpaaBoard[5][5] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(4, 5, 5, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout up
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][5] = 0;
}

TEST (Scouttest, longmovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 5 5

    ExpectedBoard.mqpaaBoard[5][9] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(5, 5, 5, 9, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to the right
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][9] = 0;

    ExpectedBoard.mqpaaBoard[0][9] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(5, 9, 0, 9, TestGame.mqGameBoard.mqpaaBoard);                       //move scout down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[0][9] = 0;

    ExpectedBoard.mqpaaBoard[0][5] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(0, 9, 0, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to left
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[0][5] = 0;

    ExpectedBoard.mqpaaBoard[5][5] = new Scout('R');                                         //expected board
    TestGame.GetNextMove(0, 5, 5, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout up
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][5] = 0;
}

TEST (Scouttest, obstaclemovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place moving scout in position 5 5
    TestGame.mqGameBoard.mqpaaBoard[5][7] = new Scout('R'); //place a scout in position 5 7
    TestGame.mqGameBoard.mqpaaBoard[3][5] = new Water('G'); //place water in position 3 5
    TestGame.mqGameBoard.mqpaaBoard[5][2] = new Water('G'); //place water in position 5 2

    ExpectedBoard.mqpaaBoard[5][5] = new Scout('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[5][7] = new Scout('R');   
    ExpectedBoard.mqpaaBoard[3][5] = new Water('G');  
    ExpectedBoard.mqpaaBoard[5][2] = new Water('G');  
    TestGame.GetNextMove(5, 5, 5, 9, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to the right, cant move because other piece in the way
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare); //stays in place

    TestGame.GetNextMove(5, 5, 5, 7, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to the right, cant move because same color piece in destination
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare); //stays in place


    TestGame.GetNextMove(5, 5, 2, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout to down, cant move becayse water in the way
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    TestGame.GetNextMove(5, 5, 3, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move scout down, cant move because water in destination
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    ExpectedBoard.mqpaaBoard[5][5] = 0;                                                      //expected board
    ExpectedBoard.mqpaaBoard[5][3] = new Scout('R');                                         
    TestGame.GetNextMove(5, 5, 5, 3, TestGame.mqGameBoard.mqpaaBoard);                       //move scout left, sucessfull
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
}
