#include "tcpserver.h"
#include "Game.h"

extern Game* game; //import global variable

TCPServer::TCPServer(QObject *parent): QObject(parent){
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    if (!server->listen(QHostAddress::Any,1234)){ //checking if the server is not able to start listening for connections on all network interfaces of the machine on port 1234

        qDebug() << "Server could not start!";
        game->setConnectionState("Server could not start");
    }
    else{
        qDebug() << "Server started";
        game->setConnectionState("Stratego Server started");
    }

}

void TCPServer::onNewConnection(){ //handle connections while they come in
    game->setConnectionState("client connected");
    QTcpSocket* socket = server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
}
