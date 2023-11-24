#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView{
public:
    //constructors
    Game(QWidget* parent = NULL); //Option of passing on a parent widget

    //public methods
    void start();
    void displayMainMenu();

    //public attributes
    QGraphicsScene* scene;
    Board* board;            //game board
    QString PlayerTurn;

};

#endif // GAME_H
