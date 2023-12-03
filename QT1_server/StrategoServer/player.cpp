#include "player.h"


Player::Player(QString NAME, QString IP, QString SOURCEPORT){
    playerName = NAME;
    playerIp = IP;
    playerSourcePort = SOURCEPORT;
}

void Player::setIP(QString ip){
    playerIp = ip;
}

void Player::setSourcePort(QString port){
    playerSourcePort = port;
}

void Player::setRoom(QString room){
    playerRoom = room;
}

QString Player::getIP(){
    return playerIp;
}

QString Player::getSourcePort(){
    return playerSourcePort;
}

QString Player::getRoom(){
    return playerRoom;
}
