#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>

class Piece: public QGraphicsRectItem{ //Piece is a QT rectangle
public:
    // constructors
    Piece(QGraphicsItem* parent = NULL);

    // getters
    char getType();

    //setters
    void setRank(char rank);
    void setOwner(QString player);


private:
    QString Owner; //belongs to which player
    char Rank; //get piece rank/type
};

#endif // PIECE_H
