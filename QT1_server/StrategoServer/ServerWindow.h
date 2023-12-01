#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include <QtSql/QSqlDatabase>

class ServerWindow: public QGraphicsView{ //Already inherits from Q_object, inside Qgrapicsview
    Q_OBJECT
public:
    //constructorss
    ServerWindow(QWidget* parent = NULL); //Option of passing on a parent widget

    //setters
    void setConnectionState(QString state);

    //public methods
    void displayVariables();
    void setDataReceived(QString ip, QString port, QString data);

    //public attributes
    QGraphicsScene* scene;

public slots:


private:
    //database
    QSqlDatabase database;
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    QGraphicsTextItem* ConnectionStateText; //QT text of the connection state
    QGraphicsTextItem* dataReceivedText; //QT text of the last data received
    QGraphicsTextItem* dataReceivedIpPortText; //QT text of the source ip and port of the data

};

#endif // SERVERWINDOW_H
