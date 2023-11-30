#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Button.h"
#include "Textbox.h"
#include "tcpsocket.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class Game: public QGraphicsView{ //Already inherits from Q_object, inside Qgrapicsview
    Q_OBJECT
public:
    //constructors
    Game(QWidget* parent = NULL); //Option of passing on a parent widget

    //public methods
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
    Board* Gameboard;            //game board
    Piece* pieceToPlace;     //piece to place in the board(clicked piece)
public slots:
    void displayMainMenu();
    void createRoom();
    void waitForJoin();
    void start();
    void ready();
    void setUpDefaultPositions();

private:
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewPiece(QString player, QString pieceRank);
    void createInitialPieces(QString player);
    void drawPieces();
    bool ArePiecesPlaced();

    //private atributes
    TCPsocket* ThisClientSocket;
    bool ArePiecesSetUp;
    QString Turn;                //string with which turn is it
    QGraphicsTextItem* TurnText; //QT text of the turn
    QList<Piece*> UnassignedUnplacedPieces; //List of pieces
    QString MessageToSend;
    void SetPiecesMessage();
    void SetRoomMessage(QString room);


    //private mainMenu atributes
    QGraphicsTextItem* titleText; //titleText
    Button* ngButton;   //newgame button
    Button* jgButton;   //joingame button
    Button* instButton; //instructions button
    Button* quitButton; //quit button
        //new game
    QGraphicsTextItem* roomText; //"Room name: "
    Textbox* roomTextbox; //where to write room
    Button* backButton;
    Button* retryConButton;
    Button* createRoomButton;
            //create room
    QGraphicsTextItem* waitingJoinText;


};

#endif // GAME_H
