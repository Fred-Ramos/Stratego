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
    QPointF toSceneCoord(int Col, int Row);
    QString getTurn();
    void setTurn(QString player);
    void pickUpPiece(Piece* piece);
    void placePiece(Piece* pieceToReplace);
    void nextPlayersTurn();
    //void removeFromPanel(Piece* piece, QString player);
    bool getArePiecesSetUp();

    //public network methods
    void setDataReceived(QString data);
    void atackMoveResponse(QString response);
    void defenseMoveResponse(QString response);

    //event
    void mouseMoveEvent(QMouseEvent* event); //when moving mouse in the game
    void mousePressEvent(QMouseEvent* event); //check if left or right click

    //public attributes
    QString thisPlayerColor; //the color of the player of this client
    QGraphicsScene* scene;
    Board* Gameboard;            //game board
    Piece* pieceToPlace;     //piece to place in the board(clicked piece)
    Piece* atackingPiece; //piece that is atacking
    Piece* defendingPiece; //piece that is defending

public slots:
    void loginGame();
    void waitForLogin();
    void waitForRegister();
    void displayMainMenu();
    void displayGameOver();
    void joinRoom();
    void createRoom();
    void createRoomClicked();
    void joinRoomClicked();
    void start();
    void ready();
    void setUpDefaultPositions();

private:
    //private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewPiece(QString player, QString pieceRank);
    void createInitialPieces(QString player);
    void drawThisPieces();
    void drawOtherPieces();
    bool ArePiecesPlaced();
    void SetLoginMessage(bool existingAcc, QString name, QString password);
    void SetRoomMessage(QString room);
    void SetJoinRoomMessage(QString room);
    void SetPiecesMessage();
    void pieceMoveMessage(int srcRow, int srcCol, int destRow, int destCol);

    //private network methods

    //private atributes
    QString thisPlayerName;  //the name of the player of this client
    QString otherPlayerName; //enemy player's name;
    bool LoggedIn;
    QString AccountName;
    QString AccountPassword;

    TCPsocket* ThisClientSocket;
    bool ArePiecesSetUp;
    QString Turn;                //string with which turn is it
    QGraphicsTextItem* player1NameText;
    QGraphicsTextItem* player2NameText;
    QGraphicsTextItem* TurnText; //QT text of the turn
    QGraphicsTextItem* lastBattleText; //last atack text
    QGraphicsTextItem* vsBattleText; //last atack text
    QList<Piece*> ThisPlayerPieces; //List of pieces
    QList<Piece*> OtherPlayerPieces; //List of pieces of other player(we dont know the ranks)
    QString MessageToSend;
    QString roomNumber;

    //private login attributes
    QGraphicsTextItem* loginNameText;
    QGraphicsTextItem* loginPasswordText;
    Textbox* loginNameTextbox;
    Textbox* loginPasswordTextbox;
    Button* loginButton;
    Button* registerButton;
    QGraphicsTextItem* waitingLoginText;
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
        //join game
            //join room
    Button* joinRoomButton;

    //otherPlayer attributes
    Piece* demoThisPiece;
    Piece* demoOtherPiece;
    void placeOtherDefeatedPiece(Piece* piece, QString rank);
    int countF;
    QPointF otherPositionF;
    int count1; //number of dead spies
    QPointF otherPosition1; //position of dead spies
    int count2;
    QPointF otherPosition2;
    int count3;
    QPointF otherPosition3;
    int count4;
    QPointF otherPosition4;
    int count5;
    QPointF otherPosition5;
    int count6;
    QPointF otherPosition6;
    int count7;
    QPointF otherPosition7;
    int count8;
    QPointF otherPosition8;
    int count9;
    QPointF otherPosition9;
    int count10;
    QPointF otherPosition10;
    int countB;
    QPointF otherPositionB;


};

#endif // GAME_H
