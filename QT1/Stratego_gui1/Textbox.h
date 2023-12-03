#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsRectItem>
#include <QTextEdit>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>

class Textbox:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Textbox(int maxlength, int textsize, bool visibility, int width, int height, QGraphicsItem* parent = NULL);

    //public methods

    //getters
    QString getWriten();

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void keyPressEvent(QKeyEvent * event);

    //public attributes

signals:
    void clicked();
private:
    //private attributes
    bool isVisible;
    QString thisToWrite;
    QGraphicsTextItem* thisToWriteText;
    int thisTextSize;
    int textMaxLength;
};


#endif // TEXTBOX_H
