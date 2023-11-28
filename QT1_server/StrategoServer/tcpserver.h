#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer: public QObject{
    Q_OBJECT
public:
    explicit TCPServer(QObject* parent = 0);
signals:

public slots:
    void onNewConnection();

private:
    QTcpServer* server;
};

#endif // TCPSERVER_H
