#include "Game.h"

#include "tcpsocket.h"

#include <QGraphicsTextItem>

extern Game* game; //import global variable

TCPsocket::TCPsocket(QObject* parent){
    socket = new QTcpSocket(this);
    ConnectionToServerStateText = new QGraphicsTextItem();
    ConnectionToServerStateText->setPlainText(QString("Server Connection: Disconnected"));
}

void TCPsocket::Connect(){
    if (socket->state() != QAbstractSocket::ConnectedState) { //if not connected, connect
        //look for local ip address

        QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();
        QString localIP;
        for (const QHostAddress &address : allAddresses) {
            if (!address.isLoopback() && address.protocol() == QAbstractSocket::IPv4Protocol) {
                localIP = address.toString();
                break;
            }
        }

        if (!localIP.isEmpty()) {
            socket->connectToHost(localIP, 1234);

            connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
            connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

            if (socket->waitForConnected(2000)){ //wait 2 seconds to connect
                ConnectionToServerStateText->setPlainText(QString("Server Connection: Connected"));
                qDebug() << "Connected!";

            }
            else{
                ConnectionToServerStateText->setPlainText(QString("Server Connection: Unsucessful Connection"));
                qDebug() << "Not Connected!";
            }
        } else {
            ConnectionToServerStateText->setPlainText(QString("Server Connection: No non-localhost IPv4 address found"));
            qDebug() << "No non-localhost IPv4 address found!";
        }
    }
}

void TCPsocket::Disconnect(){ //disconnect from server command
    if (socket->state() == QAbstractSocket::ConnectedState) { //if connected, disconnect socket
        socket->disconnectFromHost();
        ConnectionToServerStateText->setPlainText(QString("Server Connection: Unsucessful Connection"));
        qDebug() << "Disconnected!";
    }
}

void TCPsocket::onDisconnected() { //response for when server disconnects
    QTcpSocket *senderSocket = dynamic_cast<QTcpSocket*>(sender());
    if(senderSocket) {
        senderSocket->deleteLater(); // schedule the socket for deletion
        // remove the socket from list of connected sockets
    }
   ConnectionToServerStateText->setPlainText(QString("Server Connection: Lost connection"));
    qDebug() << "Server Disconnected!";
}



void TCPsocket::writeData(QString data){
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data.toUtf8());
        socket->waitForBytesWritten(3000);
    }
    qDebug() << "sent data: " << data;
}

void TCPsocket::onReadyRead(){
    // Read data from the socket
    QByteArray data = socket->readAll();
    QString receivedData = QString::fromUtf8(data);
    game->setDataReceived(receivedData);
}

