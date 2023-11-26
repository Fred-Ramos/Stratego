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
        if (getIsPlaced() == false){ //if destiny is a non placed piece, pick piece up
            game->pickUpPiece(this);
            qDebug() << "piece not placed clicked";
        }



        //CHANGE CODE BETWEEN /////// PUT INSIDE PICKUPPIECE GAME FUNCTION


        else{ //if destiny is non empty placed piece, pick piece back up
            Piece* piece;        //replace picked piece by empty piece
            piece = new Piece();
            piece->setPos(event->scenePos() - event->pos());
            piece->setOwner(QString("NOONE"));
            game->scene->addItem(piece);
            game->pickUpPiece(this);
        }

        ////////////////////


    }
    else{ //if piece is picked up
        if (getIsPlaced() == true && this->owner==QString("NOONE")){ //if destiny is a empty placed piece, place piece down
            game->placePiece(this);
            qDebug() << "piece placed clicked";
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
