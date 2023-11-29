#include "tcpsocket.h"

TCPsocket::TCPsocket(QObject* parent){
    socket = new QTcpSocket(this);
}

void TCPsocket::Connect(){
    if (socket->state() != QAbstractSocket::ConnectedState) { //if not connected, connect
        socket->connectToHost("127.0.0.1", 1234);

        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        if (socket->waitForConnected(3000)){
            qDebug() << "Connected!";
        }
        else{
            qDebug() << "Not Connected!";
        }
    }
}

void TCPsocket::Disconnect(){
    if (socket->state() == QAbstractSocket::ConnectedState) { //if connected, disconnect socket
        socket->disconnectFromHost();
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
    qDebug() << "Received from server: " << receivedData;
}

