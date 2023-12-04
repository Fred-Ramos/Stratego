#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class Player{
public:
    Player(QString NAME, QString IP, QString SOURCEPORT);

    //setters
    void setColor(QString color);
    void setIP(QString ip);
    void setSourcePort(QString port);
    void setRoom(QString room);

    //getters
    QString getName();
    QString getColor();
    QString getIP();
    QString getSourcePort();
    QString getRoom();



private:
    //private attributes
    QString playerName; //see later
    QString playerColor;
    QString playerIp;
    QString playerSourcePort;
    QString playerRoom; //room player is playing at
};

#endif // PLAYER_H
