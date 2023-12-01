#include "Textbox.h"
#include "Game.h"
#include <QBrush>

extern Game* game;

Textbox::Textbox(int maxlength, int textsize, int width, int height, QGraphicsItem *parent){
    thisTextSize = textsize;
    textMaxLength = maxlength;
    setRect(0, 0, width, height);
    setZValue(1);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(237, 214, 181));
    setBrush(brush);
    //draw box text
    thisToWrite = QString("");
    thisToWriteText = new QGraphicsTextItem(this);
    thisToWriteText->setPlainText(thisToWrite);
    QFont roomFont("Sans Serif 10", thisTextSize); //set font and size
    thisToWriteText->setFont(roomFont);
    //center text
    int xText = rect().x() + 1;
    int yText = rect().height()/2 - thisToWriteText->boundingRect().height()/2;
    thisToWriteText->setPos(xText, yText);
    thisToWriteText->setZValue(2);


    // Make the Textbox focusable
    setFlag(QGraphicsItem::ItemIsFocusable);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

QString Textbox::getWriten(){
    return thisToWrite;
}

void Textbox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //rectangle is now focused
    qDebug() << "box is now focused";
    this->setFocus();
}

void Textbox::keyPressEvent(QKeyEvent *event){
    qDebug() << "key is being pressed";
    if ( ( (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) || (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)) && thisToWrite.size() < textMaxLength) {
        qDebug() << "number is being pressed";
        // The key pressed is a number
        thisToWrite.append(QString(event->text()));
        thisToWriteText->setPlainText(thisToWrite);
        qDebug() << thisToWrite;
    }
    if (event->key() == Qt::Key_Backspace){
        thisToWrite.chop(1);
        thisToWriteText->setPlainText(thisToWrite);
        qDebug() << thisToWrite;
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
