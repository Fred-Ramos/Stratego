#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class Player{
public:
    Player(QString NAME, QString IP, QString SOURCEPORT);

    //print check matrix method
    void PrintBoard();

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


    QVector<QVector<QString>> gameBoard; //gameboard to save the pieces allocation
private:
    //private attributes
    QString playerName; //see later
    QString playerColor;
    QString playerIp;
    QString playerSourcePort;
    QString playerRoom; //room player is playing at
    //QVector<QVector<QString>> gameBoard; //gameboard to save the pieces allocation
};

#endif // PLAYER_H
