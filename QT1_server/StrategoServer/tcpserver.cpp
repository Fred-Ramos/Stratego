#include "tcpserver.h"
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
    QTcpSocket* senderSocket = dynamic_cast<QTcpSocket*>(sender());

    if(senderSocket) {
        QByteArray data = senderSocket->readAll();
        receivedfromClientData = QString::fromUtf8(data); //tansform data to QString
        serverwindow->setDataReceived(senderSocket, receivedfromClientData); // Now we can use the data
    }
}

int TCPServer::writeToClient(QTcpSocket* socket, QString data){
    if(socket->state() == QAbstractSocket::ConnectedState){
        QByteArray byteArray = data.toUtf8();        // convert QString to QByteArray
        int bytesWritten = socket->write(byteArray); //write the data itself
        socket->waitForBytesWritten();
        return bytesWritten;
    }
    else
        return -1; // return -1 or some other error code if the socket is not connected
}

void TCPServer::onClientDisconnected(){
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket) {
        senderSocket->deleteLater(); // schedule the socket for deletion
        // remove the socket from list of connected sockets
    }
    serverwindow->setConnectionState("Client disconnected"); //update client disconnected message in the scene
}
