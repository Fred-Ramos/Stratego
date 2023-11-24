#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>

class Piece: public QGraphicsRectItem{ //Piece is a QT rectangle
public:
    // constructors
    Piece(QGraphicsItem* parent = NULL);

    // getters

private:
    QString color; //color of the piece
    char Type; //get piece rank/water
};

#endif // PIECE_H
