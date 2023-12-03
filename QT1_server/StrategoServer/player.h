#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class Player{
public:
    Player(QString NAME, QString IP, QString SOURCEPORT);

    //setters
    void setIP(QString ip);
    void setSourcePort(QString port);
    void setRoom(QString room);

    //getters
    QString getIP();
    QString getSourcePort();
    QString getRoom();



private:
    //private attributes
    QString playerName; //see later
    QString playerIp;
    QString playerSourcePort;
    QString playerRoom; //room player is playing at
};

#endif // PLAYER_H
