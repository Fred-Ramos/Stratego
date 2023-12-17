#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Piece: public QGraphicsRectItem{ //Piece is a QT rectangle
public:
    // constructors
    Piece(QGraphicsItem* parent = NULL);

    // getters
    QString getRank();
    bool getIsPlaced();
    QString getOwner();
    int getiY();
    int getiX();


    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event); //when clicking on a piece

    //setters
    void setRank(QString r);
    void setOwner(QString player);
    void setIsPlaced(bool p);

    void setVisible(bool v); //set rank visible or not

    //atributes
    QPointF originalPos; //original position for this turn
    int originalZ; //original z for this turn
    QPointF originalPanelPos; //original side panel position
    int originalPanelZ; //original side panel Z

    QGraphicsTextItem* rankText;
private:
    bool isPlaced; //placed or not
    QString owner; //belongs to which player
    QString rank; //get piece rank/type
};

#endif // PIECE_H
