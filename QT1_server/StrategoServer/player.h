#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class Player{
public:
    Player(QString IP, QString SOURCEPORT);

    //setters
    QString setIP();
    QString setSourcePort();

    //getters
    QString getIP();
    QString getSourcePort();



private:
    //private attributes
    QString name; //see later
    QString ip;
    QString sourcePort;
};

#endif // PLAYER_H
