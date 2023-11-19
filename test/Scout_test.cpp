#include "../logic/game.h"


#include <gtest/gtest.h>

bool avallegalmove(BoardPiece* TestPiece,int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]){
    
    return TestPiece->IsLegalMove(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);
}

void CleanTestBoard(BoardPiece* qpaaBoard[10][10]){
    //clean board(for now because board constructor fills it up with a demo)
    //when SETUPBOARDPIECES function created, change this part:
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            qpaaBoard[i][j] = 0;
        }
    }
    /////
}

TEST (Scouttest, simplemovement){

    Game TestGame;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard);

    TestGame.mqGameBoard.mqpaaBoard[1][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 0.5
    //horizontal/vertical 1square movement, ALLOWED
	EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 2, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step forward in a columm
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 1, 6, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step forward in a row
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 0, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step back in a column
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 1, 4, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step back in a row
    //diagonal movement, NOT ALLOWED
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 2, 6, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 diagonal
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 0, 4, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 diagonal
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 2, 4, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 diagonal
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 1, 5, 0, 6, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 diagonal
    //starting position is not the pieces position, NOT ALLOWED
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 0, 0, 2, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step forward in a columm
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 2, 2, 1, 6, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step forward in a row
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 3, 4, 0, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step back in a column
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[1][5], 5, 7, 1, 4, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 1 step back in a row

}

TEST (Scouttest, longmovement){

    Game TestGame;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard);

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 5 5
    //horizontal/vertical anysquare movement, ALLOWED
	EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 9, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 4 step forward in a columm
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 5, 9, TestGame.mqGameBoard.mqpaaBoard));    //piece walks 4 step forward in a row
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 0, 5, TestGame.mqGameBoard.mqpaaBoard));     //piece walks 5 step back in a column
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 5, 0, TestGame.mqGameBoard.mqpaaBoard));     //piece walks 5 step back in a row
    
}

TEST (Scouttest, obstaclemovement){

    Game TestGame;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard);

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 5 5

    TestGame.mqGameBoard.mqpaaBoard[5][7] = new Scout('R'); //place another piece in scouts path, place scout in position 5 7

    TestGame.mqGameBoard.mqpaaBoard[2][5] = new Scout('R'); //place another piece in scouts path, place scout in position 35
    
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 5, 9, TestGame.mqGameBoard.mqpaaBoard));    //piece tries to pass over another piece; in same column
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 5, 6, TestGame.mqGameBoard.mqpaaBoard));    //piece doesnt pass over another piece; in same column
    
    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 1, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece tries to pass over another piece; in same row
    EXPECT_TRUE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 3, 5, TestGame.mqGameBoard.mqpaaBoard));    //piece doesnt pass over another piece; in same row

    TestGame.mqGameBoard.mqpaaBoard[5][7] = new Water('G'); //place water in 5 7

    EXPECT_FALSE(avallegalmove(TestGame.mqGameBoard.mqpaaBoard[5][5], 5, 5, 5, 7, TestGame.mqGameBoard.mqpaaBoard));   //cant move to water
}

TEST (Scouttest, obstaclemovement2){

    Game TestGame;

    CleanTestBoard(TestGame.mqGameBoard.mqpaaBoard);

    TestGame.mqGameBoard.mqpaaBoard[5][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 5 5

    TestGame.mqGameBoard.mqpaaBoard[5][7] = new Scout('R'); //place another piece in scouts path, place scout in position 5 7

    TestGame.mqGameBoard.mqpaaBoard[2][5] = new Scout('R'); //place another piece in scouts path, place scout in position 35
    
    
}






