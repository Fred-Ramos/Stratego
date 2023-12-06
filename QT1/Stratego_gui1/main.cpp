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
    game->loginGame(); //start the game
    //game->displayMainMenu();
=======

    //game->displayGameOver(); //start the game

<<<<<<< HEAD
    //game->loginGame(); //start the game
    game->displayMainMenu();
>>>>>>> 272cbbf9a6839fd87deea4620f7aa30f1b84015a
=======
    game->loginGame(); //start the game
    //game->displayMainMenu();
>>>>>>> 660572f81de2dac00486afb821984f8e0e0b5105
    return a.exec();
}
