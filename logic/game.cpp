#include "game.h"

#include "iostream"

//GAME CLASS
void Game :: Run(){
    using namespace std;
    Validmove = false;   //initially, set valid move as false
    do{
        ///////////////WHEN GUI MADE, THE PLAYER INPUT WILL CHANGE/////////////////////
        mqGameBoard.Print();
        // Get input and convert to coordinates
        cout << mcPlayerTurn << "'s Move: ";      //Print player colour for this turn
        int iStartMove;
        cin >> iStartMove;                        //input StartMove(piece to move)
        int iStartRow = (iStartMove / 10);    //transform RC(ROW COLUMN) into R
        int iStartCol = (iStartMove % 10);    //transform RC(ROW COLUMN) into C

        cout << "To: ";                       //"where to"
        int iEndMove;
        cin >> iEndMove;                      //input iEndMove (destination square)
        int iEndRow = (iEndMove / 10);        //transform RC(ROW COLUMN) into R
        int iEndCol = (iEndMove % 10);        //transform RC(ROW COLUMN) into C
        //////////////////////////////////////////////////////////////////////////////

        GetNextMove(iStartRow, iStartCol, iEndRow, iEndCol, mqGameBoard.mqpaaBoard);     //check move and make piece changes if necessary 
    }while(!Validmove);
 
    AlternateTurn(); //alternate turn
}   

void Game :: GetNextMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, BoardPiece* qpaaBoard[10][10]) {  //current boar as the input
    using namespace std;

    // Check that the indices are in range
    if ((iSrcRow >= 0 && iSrcRow < 10) && (iSrcCol >= 0 && iSrcCol < 10) && (iDestRow >= 0 && iDestRow < 10) && (iDestCol >= 0 && iDestCol < 10)) {
        // ADDITIONAL CHECKS IN HERE:
        BoardPiece* qpStartPiece = qpaaBoard[iSrcRow][iSrcCol]; //pointer to current piece to move
        if ((qpStartPiece != 0) && (qpStartPiece->GetColor() == mcPlayerTurn)) { //if piece is the correct color
            if (qpStartPiece->IsLegalMove(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard)) { // if destination is a valid destination

                // Make the move
                BoardPiece* qpEndPiece	            = qpaaBoard[iDestRow][iDestCol];        //store end position
                qpaaBoard[iDestRow][iDestCol]		= qpaaBoard[iSrcRow][iSrcCol];          //change end position to start position
                qpaaBoard[iSrcRow][iSrcCol]      	= 0;                                    //start position back to 0 (if move is legal, startpiece allways moves, so startposition allways goes to 0)
                // CHECK RANKS TO SEE WHICH PIECE SURVIVES IN THE ENDPOSITION
                int comp = mqGameBoard.ComparePiece(qpStartPiece, qpEndPiece);
                if (comp == 1) {   //if rank is HIGHER, keep atacking piece and delete memory of endposition piece 
                    delete qpEndPiece;
                } 
                else if (comp == -1){             // if rank lower, discard atacking piece and keep endposition piece
                    qpaaBoard[iDestRow][iDestCol]		= qpEndPiece;
                }
                else if (comp == 0){
                    qpaaBoard[iDestRow][iDestCol] = 0; //if rank equal, discard both pieces
                }
                Validmove = true;
            }
        }
    }
    if (!Validmove) {
        cout << "Invalid Move!" << endl;
    }
}

void Game :: AlternateTurn() { //change turn
    mcPlayerTurn = (mcPlayerTurn == 'R') ? 'B' : 'R';  //if RED finished, change to BLUE; else change to RED
}

bool Game :: IsGameOver(){
    //TESTING check if flag is taken or if any player has movable pieces left
    if (mqGameBoard.Legalmovesleft() == 0){ 
        return false;
    }
    else{
        if (mqGameBoard.Legalmovesleft() == -1){
            winner = 'B';
        }
        else if (mqGameBoard.Legalmovesleft() == 1){
            winner = 'R';
        } 
        return true;
    }
}