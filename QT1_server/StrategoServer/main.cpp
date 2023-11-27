#include "Game.h"
#include "myserver.h"

#include <QApplication>

Game* game; //global variable

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    myserver mServer;

    game->show();
    game->displayVariables(); //start the game
    return a.exec();
}
