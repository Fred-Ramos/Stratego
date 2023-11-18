#include "../logic/game.h"


#include <gtest/gtest.h>

bool aval(BoardPiece* TestPiece,int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]){
    
    return TestPiece->IsLegalMove(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);
}

TEST (ExampleTests, Scout_movement){
    Board TestBoard;

    //clean board(for now because board constructor fills it up with a demo)
    //when SETUPBOARDPIECES function created, change this part:
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            TestBoard.mqpaaBoard[i][j] = 0;
        }
    }
    /////

    TestBoard.mqpaaBoard[1][5] = new Scout('R'); //test Scout piece legalmoves, place scout in position 0.5

	EXPECT_TRUE(aval(TestBoard.mqpaaBoard[1][5], 1, 5, 2, 5, TestBoard.mqpaaBoard));    //piece walks 1 step forward in a columm
    EXPECT_TRUE(aval(TestBoard.mqpaaBoard[1][5], 1, 5, 1, 6, TestBoard.mqpaaBoard));   //piece walks 1 step forward in a row
    EXPECT_TRUE(aval(TestBoard.mqpaaBoard[1][5], 1, 5, 0, 5, TestBoard.mqpaaBoard));  //piece walks 1 step back in a column
    EXPECT_TRUE(aval(TestBoard.mqpaaBoard[1][5], 1, 5, 1, 4, TestBoard.mqpaaBoard));   //piece walks 1 step back in a row
}