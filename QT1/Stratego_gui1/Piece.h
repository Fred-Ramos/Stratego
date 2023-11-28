#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Piece: public QGraphicsRectItem{ //Piece is a QT rectangle
public:
    // constructors
    Piece(QGraphicsItem* parent = NULL);

    // getters
    char getRank();
    bool getIsPlaced();
    QString getOwner();


    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event); //when clicking on a piece

    //setters
    void setRank(char r);
    void setOwner(QString player);
    void setIsPlaced(bool p);

    //atributes
    QPointF originalPos;


private:
    bool isPlaced; //placed or not
    QString owner; //belongs to which player
    char rank; //get piece rank/type
};

#endif // PIECE_H
