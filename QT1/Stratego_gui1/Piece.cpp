#include "Piece.h"
#include "Game.h"

#include <QBrush>
#include <QGraphicsSceneMouseEvent>

extern Game* game;

#include <QDebug>

Piece::Piece(QGraphicsItem *parent){
    //create the square
    setRect(0, 0, 50, 50);
}

bool Piece::getIsPlaced(){
    return isPlaced;
}

QString Piece::getOwner(){
    return owner;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << game->pieceToPlace;
    if (game->pieceToPlace == NULL){ //if no piece is picked up
        game->pickUpPiece(this);
        qDebug() << "piece not placed clicked";
    }
    else{ //if a piece is already picked up
        qDebug() << "there is a piece picked up";

        if (getIsPlaced() == true && this->owner==QString("NOONE")){ //if destiny is a empty placed piece, place piece down
            qDebug() << "piece placed clicked";
            game->placePiece(this);
        }
    }
}

void Piece::setOwner(QString player){
    //set owner
    owner = player;
    //change color
    if (player == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(237, 214, 181));
        setBrush(brush);
    }
    else if (player == QString("REDPLAYER")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
    else if (player == QString("BLUEPLAYER")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }
}

void Piece::setIsPlaced(bool p){
    isPlaced = p;
}
