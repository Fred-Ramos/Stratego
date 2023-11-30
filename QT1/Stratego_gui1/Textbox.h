#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsRectItem>
#include <QTextEdit>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class Textbox:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Textbox(QString name, int width, int height, QGraphicsItem* parent = NULL);

    //public methods
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void keyPressEvent(QKeyEvent * event);
signals:
    void clicked();
private:
    QString roomNumber;
    QGraphicsTextItem* roomNumberText;
};


#endif // TEXTBOX_H
