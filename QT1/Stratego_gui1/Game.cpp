#include "Game.h"

Game::Game(QWidget *parent){
    //Set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(855, 555);

    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 855, 555); //scene same size of the screen
    setScene(scene);
}

void Game::start(){
    //test code TODO REMOVE LATER
    board = new Board();
    board->placePieces();
}
