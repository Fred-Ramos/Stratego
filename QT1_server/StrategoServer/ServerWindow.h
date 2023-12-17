#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "player.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include <QTcpSocket>

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
    void setDataReceived(QTcpSocket* socket, QString data);

    //public attributes
    QGraphicsScene* scene;

public slots:


private:
    //player this session data
    QList<Player*> Players; //List of players


    //database
    QSqlDatabase database;
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    QString setLoginResponse(QString receivedUsername, QString receivedPassword);

    QString setRegisterResponse(QString receivedUsername, QString receivedPassword);

    QString setRoomResponse(Player* player, QString data);
    void setJoinRoomResponse(Player* thisPlayer, QTcpSocket* thisSocket, QString thisIp, QString thisSourcePort, QString thisRoom);
    void setMoveResponse(Player* thisPlayer, QTcpSocket* thisSocket, QString thisIp, QString thisSourcePort, QString thisMove);

    QGraphicsTextItem* ConnectionStateText; //QT text of the connection state
    QGraphicsTextItem* dataReceivedText; //QT text of the last data received
    QGraphicsTextItem* dataReceivedIpPortText; //QT text of the source ip and port of the data

    void setPiecesResponse(Player* thisPlayer, QTcpSocket* thisSocket, QString thisIp, QString thisSourcePort, QString PositionData);

    int ComparePiece(QString thisRank, QString otherRank);


};

#endif // SERVERWINDOW_H
