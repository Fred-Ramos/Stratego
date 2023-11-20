#include "testfunctions.h"

#include <gtest/gtest.h>

TEST (Minertest, simplemovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Miner('R'); //test Miner piece legalmoves, place Miner in position 5 5

    ExpectedBoard.mqpaaBoard[5][6] = new Miner('R');                                         //expected board
    TestGame.GetNextMove(5, 5, 5, 6, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to the right
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][6] = 0;

    ExpectedBoard.mqpaaBoard[4][6] = new Miner('R');                                         //expected board
    TestGame.GetNextMove(5, 6, 4, 6, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[4][6] = 0;

    ExpectedBoard.mqpaaBoard[4][5] = new Miner('R');                                         //expected board
    TestGame.GetNextMove(4, 6, 4, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to left
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[4][5] = 0;

    ExpectedBoard.mqpaaBoard[5][5] = new Miner('R');                                         //expected board
    TestGame.GetNextMove(4, 5, 5, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner up
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
    ExpectedBoard.mqpaaBoard[5][5] = 0;
}

TEST (Minertest, longmovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Miner('R'); //test Miner piece legalmoves, place Miner in position 5 5(Miner should not move)

    ExpectedBoard.mqpaaBoard[5][5] = new Miner('R');                                         //expected board
    TestGame.GetNextMove(5, 5, 5, 9, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to the right
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
                                      
    TestGame.GetNextMove(5, 9, 0, 9, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    TestGame.GetNextMove(0, 9, 0, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to left
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);

    TestGame.GetNextMove(0, 5, 5, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner up
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
}

TEST (Minertest, obstaclemovement){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Miner('R'); //test Miner piece legalmoves, place moving Miner in position 5 5
    TestGame.mqGameBoard.mqpaaBoard[5][6] = new Miner('R'); //place a Miner in position 5 6
    TestGame.mqGameBoard.mqpaaBoard[4][5] = new Water('G'); //place water in position 4 5

    ExpectedBoard.mqpaaBoard[5][5] = new Miner('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[5][6] = new Miner('R');   
    ExpectedBoard.mqpaaBoard[4][5] = new Water('G');  

    TestGame.GetNextMove(5, 5, 5, 6, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to the right, cant move because same color piece in destination
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare); //stays in place


    TestGame.GetNextMove(5, 5, 4, 5, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner down, cant move because water in destination
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard); //compare boards
    EXPECT_TRUE(compare);
}

TEST (Minertest, turn){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner turn move, place red Miner in position 5 5
    TestGame.mqGameBoard.mqpaaBoard[9][1] = new Miner('B'); //test Miner turn move, place blue Miner in position 5 6

    ExpectedBoard.mqpaaBoard[9][0] = 0;                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Miner('B');
    ExpectedBoard.mqpaaBoard[8][0] = new Miner('R');                                       
    ExpectedBoard.mqpaaBoard[8][1] = 0;                                        
    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move red Miner down
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);

    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //put red Miner back in position
    TestGame.mqGameBoard.mqpaaBoard[8][0] = 0;

    ExpectedBoard.mqpaaBoard[9][0] = new Miner('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Miner('B');
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                        
    ExpectedBoard.mqpaaBoard[8][1] = 0;
    TestGame.GetNextMove(9, 1, 8, 1, TestGame.mqGameBoard.mqpaaBoard);                       //move blue Miner down(shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);  

    TestGame.AlternateTurn(); //change to blue turn, and redo tests     

    ExpectedBoard.mqpaaBoard[9][0] = new Miner('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = new Miner('B');
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                       
    ExpectedBoard.mqpaaBoard[8][1] = 0;                                        
    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move red Miner down (shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);

    ExpectedBoard.mqpaaBoard[9][0] = new Miner('R');                                         //expected board
    ExpectedBoard.mqpaaBoard[9][1] = 0;
    ExpectedBoard.mqpaaBoard[8][0] = 0;                                        
    ExpectedBoard.mqpaaBoard[8][1] = new Miner('B');
    TestGame.GetNextMove(9, 1, 8, 1, TestGame.mqGameBoard.mqpaaBoard);                       //move blue Miner down(shouldnt move)
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare);  
}

TEST (Minertest, hierarchy){

	Game TestGame;

    Board ExpectedBoard;

    bool compare;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard); //clean board
    CleanTestBoard(ExpectedBoard.mqpaaBoard);        //clean board
    ////Miner
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R');  //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Spy('B');  //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Miner('R');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Scout
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Scout('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Miner('R');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Miner
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Miner('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = 0;

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Sergeant
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Sergeant('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Sergeant('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Lieutenant
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Lieutenant('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Lieutenant('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Captain
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Captain('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Captain('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Major
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Major('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Major('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Colonel
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Colonel('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Colonel('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////General
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new General('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new General('B');

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Marshal
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Marshal('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Marshal('B');      

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
    ////Bomb
    TestGame.mqGameBoard.mqpaaBoard[9][0] = new Miner('R'); //test Miner hierarchy, place red Miner in 9 0
    TestGame.mqGameBoard.mqpaaBoard[8][0] = new Bomb('B');   //place blue Miner in 8 0

    ExpectedBoard.mqpaaBoard[9][0] = 0;                    //expected board
    ExpectedBoard.mqpaaBoard[8][0] = new Miner('R'); //Miner SHOULD survive bomb

    TestGame.GetNextMove(9, 0, 8, 0, TestGame.mqGameBoard.mqpaaBoard);                       //move Miner to enemy piece
    compare = CompareBoards(ExpectedBoard.mqpaaBoard, TestGame.mqGameBoard.mqpaaBoard);      //compare boards
    EXPECT_TRUE(compare); 
}