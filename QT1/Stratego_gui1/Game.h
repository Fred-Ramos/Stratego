#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView{ //Already inherits from Q_object, inside Qgrapicsview
    Q_OBJECT
public:
    //constructors
    Game(QWidget* parent = NULL); //Option of passing on a parent widget

    //public methods
    void displayMainMenu();

    //public attributes
    QGraphicsScene* scene;
    Board* board;            //game board
    QString PlayerTurn;
public slots:
    void start();
};

#endif // GAME_H
