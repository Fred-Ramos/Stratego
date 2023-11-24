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

void Game::displayMainMenu(){
    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 150;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);
}
