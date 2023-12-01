#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class ServerWindow: public QGraphicsView{ //Already inherits from Q_object, inside Qgrapicsview
    Q_OBJECT
public:
    //constructorss
    ServerWindow(QWidget* parent = NULL); //Option of passing on a parent widget

    //setters
    void setConnectionState(QString state);

    //public methods
    void displayVariables();
    void setDataReceived(QString data);

    //public attributes
    QGraphicsScene* scene;

public slots:


private:
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    QGraphicsTextItem* ConnectionStateText; //QT text of the connection state
    QGraphicsTextItem* dataReceivedText; //QT text of the lasta data received

};

#endif // SERVERWINDOW_H
