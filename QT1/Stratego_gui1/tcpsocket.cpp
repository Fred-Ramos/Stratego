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
        socket->connectToHost("127.0.0.1", 1234);

        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        if (socket->waitForConnected(2000)){ //wait 2 seconds to connect
            ConnectionToServerStateText->setPlainText(QString("Server Connection: Connected"));
            qDebug() << "Connected!";

        }
        else{
            ConnectionToServerStateText->setPlainText(QString("Server Connection: Unsucessful Connection"));
            qDebug() << "Not Connected!";
        }
    }
}

void TCPsocket::Disconnect(){
    if (socket->state() == QAbstractSocket::ConnectedState) { //if connected, disconnect socket
        socket->disconnectFromHost();
        ConnectionToServerStateText->setPlainText(QString("Server Connection: Unsucessful Connection"));
        qDebug() << "Disconnected!";
    }
}

void TCPsocket::writeData(QString data){
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data.toUtf8());
        socket->waitForBytesWritten(3000);
    }
}

void TCPsocket::onReadyRead(){
    // Read data from the socket
    QByteArray data = socket->readAll();
    QString receivedData = QString::fromUtf8(data);
    game->setDataReceived(receivedData);
}

