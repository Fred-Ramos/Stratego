#include "Board.h"
#include "Game.h"

#include <QDebug>
extern Game* game; //import global variable

Board::Board(){

}

void Board::addPiece(Piece *piece){
    pieces.append(piece);
}

QList<Piece *> Board::getPieces(){
    return pieces; //return private pieces list
}

void Board::placePieces(int x, int y){ //create grid of pieces (skeleton of board)
    //create grid
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j++){
            Piece* piece = new Piece(); //create empty piece
            piece->setPos(x + i*55, y + j*55); //set piece position (with spacing 5, pieces dont collid with each other)
            addPiece(piece); //append piece to pieces list
            game->scene->addItem(piece);
            //set owner to NOONE initially
            piece->setOwner(QString("NOONE"));
            piece->setIsPlaced(true);
            qDebug() << "piece added to board, owner:" << piece->getOwner() << " placed: " << piece->getIsPlaced() ;
        }
    }
}
