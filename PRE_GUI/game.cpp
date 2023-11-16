#include "game.h"

#include "iostream"

//GAME CLASS
void Game :: Start(){
    GetNextMove(mqGameBoard.mqpaaBoard);     //get input for next move 
    AlternateTurn();                         //alternate turn
}

void Game :: GetNextMove(BoardPiece* qpaaBoard[10][10]) {  //current boar as the input
    using namespace std;
    bool bValidMove		= false;   //initially, set valid move as false
    do {                           //while no valid move has been given:
        mqGameBoard.Print();

        // Get input and convert to coordinates
        cout << mcPlayerTurn << "'s Move: ";      //Print player colour for this turn
        int iStartMove;
        cin >> iStartMove;                        //input StartMove(piece to move)
        int iStartRow = (iStartMove - 11) / 10;    //transform RC(ROW COLUMN) into R
        int iStartCol = (iStartMove - 11) % 10;    //transform RC(ROW COLUMN) into C

        cout << "To: ";                           //"where to"
        int iEndMove;
        cin >> iEndMove;                          //input iEndMove (destination square)
        int iEndRow = (iEndMove - 11)/ 10;        //transform RC(ROW COLUMN) into R
        int iEndCol = (iEndMove - 11)% 10;        //transform RC(ROW COLUMN) into C

        // Check that the indices are in range
        if ((iStartRow >= 0 && iStartRow < 10) && (iStartCol >= 0 && iStartCol < 10) && (iEndRow >= 0 && iEndRow < 10) && (iEndCol >= 0 && iEndCol < 10)) {
            // ADDITIONAL CHECKS IN HERE:
            BoardPiece* qpStartPiece = qpaaBoard[iStartRow][iStartCol]; //pointer to current piece to move
            if ((qpStartPiece != 0) && (qpStartPiece->GetColor() == mcPlayerTurn)) { //if piece is the correct color
                if (qpStartPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard)) { // if destination is a valid destination

                    // Make the move
                    BoardPiece* qpEndPiece					= qpaaBoard[iEndRow][iEndCol];        //store end position
                    qpaaBoard[iEndRow][iEndCol]		=     qpaaBoard[iStartRow][iStartCol];    //change end position to start position
                    qpaaBoard[iStartRow][iStartCol]	= 0;                                      //start position back to 0 (if move is legal, startpiece allways moves, so startposition allways goes to 0)
                    // CHECK RANKS TO SEE WHICH PIECE SURVIVES IN THE ENDPOSITION
                    int comp = mqGameBoard.ComparePiece(qpStartPiece, qpEndPiece);
                    if (comp == 1) {   //if rank is HIGHER, keep atacking piece and delete memory of endposition piece 
                        delete qpEndPiece;
                    } 
                    else if (comp == -1){             // if rank lower, discard atacking piece and keep endposition piece
                        qpaaBoard[iEndRow][iEndCol]		= qpEndPiece;
                    }
                    else if (comp == 0){
                        qpaaBoard[iEndRow][iEndCol] = 0; //if rank equal, discard both pieces
                    }
                    bValidMove = true;
                }
            }
        }
        if (!bValidMove) {
            cout << "Invalid Move!" << endl;
        }
    } while (!bValidMove);
}

void Game :: AlternateTurn() { //change turn
    mcPlayerTurn = (mcPlayerTurn == 'R') ? 'B' : 'R';  //if RED finished, change to BLUE; else change to RED
}

bool Game :: IsGameOver(){
    //TESTING check if flag is taken or if any player has movable pieces left
    return false;
}