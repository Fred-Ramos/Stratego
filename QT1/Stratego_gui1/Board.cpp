#include "Board.h"
#include "Game.h"

extern Game* game; //import global variable

Board::Board(){

}

QList<Piece *> Board::getPieces(){
    return pieces; //return private pieces list
}

void Board::placePieces(int x, int y, int cols, int rows){ //create grid of pieces (skeleton of board)
    //create grid
    for (size_t i = 0; i < cols; i++){
        for (size_t j = 0; j < rows; j++){
            Piece* piece = new Piece(); //create empty piece
            piece->setPos(x + i*55, y + j*55); //set piece position (with spacing 5, pieces dont collid with each other)
            pieces.append(piece); //append piece to pieces list
            game->scene->addItem(piece);
        }
    }
}
