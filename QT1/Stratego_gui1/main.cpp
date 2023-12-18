#include "Game.h"

#include <QApplication>

Game* game; //global variable


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    game->show();
    game->loginGame(); //start the game
    //game->displayInstructions();

    return a.exec();
}
