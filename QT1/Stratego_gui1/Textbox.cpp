#include "Textbox.h"

#include <QBrush>


Textbox::Textbox(QString name, int width, int height, QGraphicsItem *parent){
    setRect(0, 0, width, height);
    setZValue(1);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(237, 214, 181));
    setBrush(brush);

    //draw box text
    roomNumber = name;
    roomNumberText = new QGraphicsTextItem(roomNumber, this);
    roomNumberText->setPlainText(roomNumber);
    QFont roomFont("Sans Serif 10", 15); //set font and size
    roomNumberText->setFont(roomFont);
    //center text
    int xText = rect().x() + 1;
    int yText = rect().height()/2 - roomNumberText->boundingRect().height()/2;
    roomNumberText->setPos(xText, yText);
    roomNumberText->setZValue(2);


    // Make the Textbox focusable
    setFlag(QGraphicsItem::ItemIsFocusable);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

void Textbox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //rectangle is now focused
    qDebug() << "box is now focused";
    this->setFocus();
}

void Textbox::keyPressEvent(QKeyEvent *event){
    qDebug() << "key is being pressed";
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9 && roomNumber.size() < 6) {
        qDebug() << "number is being pressed";
        // The key pressed is a number
        roomNumber.append(QString(event->text()));
        roomNumberText->setPlainText(roomNumber);
        qDebug() << roomNumber;
    }
    if (event->key() == Qt::Key_Backspace){
        roomNumber.chop(1);
        roomNumberText->setPlainText(roomNumber);
        qDebug() << roomNumber;
    }
}

void Textbox::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    //change color to gray
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
    this->setOpacity(0.5);
}

void Textbox::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    //change color back to background color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(237, 214, 181));
    setBrush(brush);
    this->setOpacity(1);
}
