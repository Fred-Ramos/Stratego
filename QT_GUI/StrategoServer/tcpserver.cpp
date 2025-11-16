#include "tcpserver.h"
#include "ServerWindow.h"

extern ServerWindow* serverwindow; //import global variable

TCPServer::TCPServer(QObject *parent): QObject(parent){
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    //look for lan ip address
    QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();
    QString localIP;
    for (const QHostAddress &address : allAddresses) {
        if (!address.isLoopback() && address.protocol() == QAbstractSocket::IPv4Protocol) {
            localIP = address.toString();
            break;
        }
    }

    //start listening to connections
    if (localIP.isEmpty()) {
        qDebug() << "No non-localhost IPv4 address found!";
        serverwindow->setConnectionState("No non-localhost IPv4 address found");
    } else {
        if (!server->listen(QHostAddress(localIP),1234)){
            qDebug() << "Server could not start!";
            serverwindow->setConnectionState("Server could not start");
        }
        else{
            qDebug() << "Server started in local IP: " << localIP << " || In port: 1234";
            serverwindow->setConnectionState("Stratego Server started");
            serverwindow->setIPText(localIP);
        }
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

//QString clientID = socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()); ADD IDENTIFIER???


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
        qDebug() << "Sent Message" << data;
        return bytesWritten;
    }
    else
        return -1; // return -1 or some other error code if the socket is not connected
}

void TCPServer::onClientDisconnected(){
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    serverwindow->setDataReceived(senderSocket, QString("LEAVE"));
    if(senderSocket) {
        senderSocket->deleteLater(); // schedule the socket for deletion
        // remove the socket from list of connected sockets
    }
    serverwindow->setConnectionState("Client disconnected"); //update client disconnected message in the scene
}

#include <QTcpSocket>

QTcpSocket *TCPServer::findConnection(QString ip, QString port){ //see through sockets and find the one with correspondent ip and port
    QList<QTcpSocket*> sockets = this->findChildren<QTcpSocket*>(); //this == server
    for (QTcpSocket* socket : sockets) {
        if (socket->peerAddress().toString() == ip && QString::number(socket->peerPort()) == port) {
            return socket;
        }
    }
    return nullptr;
}
