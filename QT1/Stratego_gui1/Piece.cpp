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
    //if this piece is not placed yet, then pick it up
    if (getIsPlaced() == false){
        game->pickUpPiece(this);
        qDebug() << "piece not placed clicked";
    }

    //if this piece is placed, then replace it
    else if (getIsPlaced() == true && game->getArePiecesSetUp() == false){ //and if pieces not setup yet
        game->placePiece(this);
        qDebug() << "piece placed clicked";
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
