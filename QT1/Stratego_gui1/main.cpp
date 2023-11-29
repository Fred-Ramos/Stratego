#include "Game.h"
#include "tcpsocket.h"

#include <QApplication>

Game* game; //global variable
TCPsocket* clientSocket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    clientSocket = new TCPsocket(); //connect later in ready button

    game->show();
    game->displayMainMenu(); //start the game
    return a.exec();
}
