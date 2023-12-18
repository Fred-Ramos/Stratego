#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QGraphicsView>
#include <QDebug>

class TCPsocket: public QObject
{
    Q_OBJECT
public:
    explicit TCPsocket(QObject* parent = 0);

    //public methods
    void writeData(QString data);
    void readData();

    void Disconnect();

    //public attributes
    QGraphicsTextItem* ConnectionToServerStateText; //QT text of the connection state

signals:

public slots:
    void onDisconnected();
    void onReadyRead();
    void Connect();

private:
    //private attributes
    QString serverIP;
    QTcpSocket* socket;
    QString receivedfromServerData;
};

#endif // TCPSOCKET_H
