#include "Game.h"
#include "tcpserver.h"

#include <QApplication>

Game* game; //global variable

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    TCPServer gameServer;

    game->show();
    game->displayVariables(); //start the game
    return a.exec();
}
