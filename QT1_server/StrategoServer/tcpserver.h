#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer: public QObject{
    Q_OBJECT
public:
    //constructor
    explicit TCPServer(QObject* parent = 0);

    //public atributes
    QString receivedData;
signals:

public slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer* server;
};

#endif // TCPSERVER_H
