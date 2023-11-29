#include "tcpserver.h"
#include "ServerWindow.h"

extern ServerWindow* serverwindow; //import global variable

TCPServer::TCPServer(QObject *parent): QObject(parent){
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    if (!server->listen(QHostAddress::Any,1234)){ //checking if the server is not able to start listening for connections on all network interfaces of the machine on port 1234

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

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
}

void TCPServer::onReadyRead(){
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket) {
        QByteArray data = senderSocket->readAll();
        receivedData = QString::fromUtf8(data);
        serverwindow->setDataReceived(receivedData);
        // Now we can use strData
    }
}
