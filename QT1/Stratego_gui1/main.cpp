#include "Game.h"

#include <QApplication>

Game* game; //global variable


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    game->show();
<<<<<<< HEAD
    game->displayGameOver(); //start the game
=======
    game->loginGame(); //start the game
    //game->displayMainMenu();
>>>>>>> c074d6bdd1c75757ee91d6739b6c459fa21841a2
    return a.exec();
}
