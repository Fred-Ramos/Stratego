#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class TCPsocket: public QObject
{
    Q_OBJECT
public:
    explicit TCPsocket(QObject* parent = 0);

    //public methods
    void writeData(QString data);
    void readData();

    void Connect();
    void Disconnect();
signals:

public slots:
    void onReadyRead();

private:
    //private attributes
    QTcpSocket* socket;
    QString receivedfromServerData;
};

#endif // TCPSOCKET_H
