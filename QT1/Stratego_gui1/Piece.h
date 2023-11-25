#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>

class Piece: public QGraphicsRectItem{ //Piece is a QT rectangle
public:
    // constructors
    Piece(QGraphicsItem* parent = NULL);

    // getters
    char getType();
    bool GetisPlaced();
    QString getOwner();

    //setters
    void setRank(char rank);
    void setOwner(QString player);
    void setisPlaced(bool p);


private:
    bool isPlaced; //placed or not
    QString Owner; //belongs to which player
    char Rank; //get piece rank/type
};

#endif // PIECE_H
