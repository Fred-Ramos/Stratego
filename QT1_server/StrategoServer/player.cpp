#include "player.h"

#include <QDebug>


Player::Player(QString NAME, QString IP, QString SOURCEPORT){
    playerName = NAME;
    playerIp = IP;
    playerSourcePort = SOURCEPORT;
    playerRoom = QString("");

    //initialize gameboard
    gameBoard = QVector<QVector<QString>>(10, QVector<QString>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ( (i == 4 || i == 5) && (j == 2 || j == 3 || j == 6 || j == 7) ){ //if it is a water position, put Water
                gameBoard[i][j] = QString("W"); //water
            }
            else{
                gameBoard[i][j] = QString("N"); //empty
            }
            if (i == j ){
                gameBoard[i][j] = QString("M"); //teste
            }
        }
    }


}

void Player::PrintBoard(){
    qDebug() << "Matrix:";
    for (int i = 0; i < 10; i++) {
        QString row;
        for (int j = 0; j < 10; j++) {
            row += QString("%1 ").arg(gameBoard[i][j]);
        }
        qDebug() << row;
    }
}

void Player::setColor(QString color){
    playerColor = color;
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

QString Player::getName(){
    return playerName;
}

QString Player::getColor(){
    return playerColor;
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

QVector<QVector<QString>> Player::invertBoard(){
    QVector<QVector<QString>> rotatedBoard(10, QVector<QString>(10));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            int rotatedI = 9 - i; // Rotate around the center of the board
            int rotatedJ = 9 - j; // Rotate around the center of the board
            rotatedBoard[rotatedI][rotatedJ] = gameBoard[i][j];
        }
    }
    gameBoard = rotatedBoard;
    return rotatedBoard;
}
