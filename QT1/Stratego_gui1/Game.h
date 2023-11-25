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
    QString getTurn();
    void setTurn(QString player);
    //public attributes
    QGraphicsScene* scene;
    Board* board;            //game board
    Piece* pieceToPlace;     //piece to place in the board(initially)
public slots:
    void start();

private:
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewPiece(QString player);
    void createInitialPieces();
    void drawPieces();
    //private atributes
    QString Turn;                //string with which turn is it
    QGraphicsTextItem* TurnText; //QT text of the turn
    QList<Piece*> redPieces; //List of pieces
    QList<Piece*> bluePieces;

};

#endif // GAME_H
