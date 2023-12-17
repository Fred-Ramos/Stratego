#include "Button.h"

#include <QBrush>
Button::Button(QString name, int width, int height, QGraphicsItem *parent){
    //draw rectangle
    setRect(0,0, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    //draw button text
    QGraphicsItem* text;
    text = new QGraphicsTextItem(name, this); //button is the parent of the text
    //center text
    int xText = rect().width()/2 - text->boundingRect().width()/2;
    int yText = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xText, yText);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked(); //emit clicked signal when button pressed
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    //change color to dark red
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    //change color back to red
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}
