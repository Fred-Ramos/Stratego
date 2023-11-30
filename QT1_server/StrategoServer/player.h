#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class Player{
public:
    Player(QTcpSocket *socket, int room);

private:
    //private attributes
    QTcpSocket *socket;
};

#endif // PLAYER_H
