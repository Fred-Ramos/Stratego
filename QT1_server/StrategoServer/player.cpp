#include "player.h"


Player::Player(QString IP, QString SOURCEPORT){
    ip = IP;
    sourcePort = SOURCEPORT;

}

QString Player::getIP(){
    return ip;
}

QString Player::getSourcePort(){
    return sourcePort;
}
