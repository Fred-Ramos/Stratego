#include "Piece.h"

#include <QBrush>

Piece::Piece(QGraphicsItem *parent){
    //create the square
    setRect(0, 0, 50, 50);
    //select color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(237, 214, 181));
    setBrush(brush);
}

void Piece::setOwner(QString player){
    Owner = player;
}
