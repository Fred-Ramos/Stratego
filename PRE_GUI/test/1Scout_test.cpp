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

TEST (Scouttest, turn){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout turn move, place red scout in position 5 5
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Scout('B'); //test Scout turn move, place blue scout in position 5 6

    ExpectedBoard.mqpaaBoard[9][0] = 0;                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Scout('B');
    ExpectedBoard.mqpaaBoard[8][0] = new Scout('R');                                       
    ExpectedBoard.mqpaaBoard[8][1] = 0;                                        
    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move red scout down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //put red scout back in position
    TestGame.mqGameBoard.mqpaaBoard[8][0] = 0;

    ExpectedBoard.mqpaaBoard[9][0] = new Scout('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Scout('B');
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                        
    ExpectedBoard.mqpaaBoard[8][1] = 0;
    TestGame.GetNextMove(9, 1, 8, 1, TestGame.mqGameBoard.mqpaaBoard);                       //move blue scout down(shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);  

    TestGame.AlternateTurn(); //change to blue turn, and redo tests     

    ExpectedBoard.mqpaaBoard[9][0] = new Scout('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Scout('B');
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                       
    ExpectedBoard.mqpaaBoard[8][1] = 0;                                        
    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move red scout down (shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);

    ExpectedBoard.mqpaaBoard[9][0] = new Scout('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = 0;
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                        
    ExpectedBoard.mqpaaBoard[8][1] = new Scout('B');
    TestGame.GetNextMove(9, 1, 8, 1, TestGame.mqGameBoard.mqpaaBoard);                       //move blue scout down(shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);  
}

TEST (Scouttest, hierarchy){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board
    ////Spy
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Spy('B');   //place blue spy in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Scout('R');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Scout
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Scout('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = 0;

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Miner
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Miner('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Miner('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Sergeant
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Sergeant('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Sergeant('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Lieutenant
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Lieutenant('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Lieutenant('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Captain
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Captain('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Captain('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Major
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Major('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Major('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Colonel
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Colonel('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Colonel('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////General
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new General('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new General('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Marshal
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Marshal('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Marshal('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Bomb
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Scout('R'); //test Scout hierarchy, place red scout in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Bomb('B');   //place blue scout in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = 0;

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Scout to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
}


