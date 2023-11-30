#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "player.h"

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer: public QObject{
    Q_OBJECT
public:
    //constructor
    explicit TCPServer(QObject* parent = 0);

    //public atributes
signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    //private attributes
    QTcpServer* server;
    QList<Player*> clients;
    QString receivedfromClientData;
};

#endif // TCPSERVER_H
