#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class Game: public QGraphicsView{ //Already inherits from Q_object, inside Qgrapicsview
    Q_OBJECT
public:
    //constructors
    Game(QWidget* parent = NULL); //Option of passing on a parent widget

    //public methods
    void displayMainMenu();
    QString getTurn();
    void setTurn(QString player);
    void pickUpPiece(Piece* piece);
    void placePiece(Piece* pieceToReplace);
    void nextPlayersTurn();
    void removeFromPanel(Piece* piece, QString player);
    bool getArePiecesSetUp();

    //event
    void mouseMoveEvent(QMouseEvent* event); //when moving mouse in the game
    void mousePressEvent(QMouseEvent* event); //check if left or right click

    //public attributes
    QGraphicsScene* scene;
    Board* board;            //game board
    Piece* pieceToPlace;     //piece to place in the board(clicked piece)
public slots:
    void start();
    void ready();

private:
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewPiece(QString player, QString pieceRank);
    void createInitialPieces();
    void drawPieces();
    bool ArePiecesPlaced();

    //private atributes
    bool ArePiecesSetUp;
    QString Turn;                //string with which turn is it
    QGraphicsTextItem* TurnText; //QT text of the turn
    QList<Piece*> redUnplacedPieces; //List of pieces

    //later on remove blueunplacedpieces
    //placed pieces will be gray, and red/blue color will randomly be attributed when 2players connect
    QList<Piece*> blueUnplacedPieces;

};

#endif // GAME_H
