#include "tcpserver.h"
#include "player.h"
#include "ServerWindow.h"

extern ServerWindow* serverwindow; //import global variable

TCPServer::TCPServer(QObject *parent): QObject(parent){
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    if (!server->listen(QHostAddress("127.0.0.1"),1234)){ //checking if the server is not able to start listening for connections on all network interfaces of the machine on port 1234

        qDebug() << "Server could not start!";
        serverwindow->setConnectionState("Server could not start");
    }
    else{
        qDebug() << "Server started";
        serverwindow->setConnectionState("Stratego Server started");
    }

}

void TCPServer::onNewConnection(){ //handle connections while they come in
    serverwindow->setConnectionState("New client connected");
    QTcpSocket* socket = server->nextPendingConnection();
    QString connectionIP = socket->peerAddress().toString();
    QString connectionSourcePort = QString::number(socket->peerPort());

    qDebug() << "New client connected: " << connectionIP << " from port: " << connectionSourcePort;

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
}

//QString clientKey = socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()); ADD IDENTIFIER???







void TCPServer::onReadyRead(){
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    QString connectionIP = senderSocket->peerAddress().toString();
    QString connectionSourcePort = QString::number(senderSocket->peerPort());

    qDebug() << "New data from client: " << connectionIP << " from port: " << connectionSourcePort;

    if(senderSocket) {
        QByteArray data = senderSocket->readAll();
        receivedfromClientData = QString::fromUtf8(data);
        serverwindow->setDataReceived(connectionIP, connectionSourcePort, receivedfromClientData); // Now we can use the data
    }
}

void TCPServer::onClientDisconnected(){
    serverwindow->setConnectionState("Client disconnected");
}
