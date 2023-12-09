#include "Game.h"
#include "Button.h"
#include "Textbox.h"
#include "tcpsocket.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

#include <QDebug>

Game::Game(QWidget *parent){ //constructor
    //Set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(855, 573);

    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 855, 573); //scene same size of the screen
    setScene(scene);

    //initialize variables
    MessageToSend = QString("");
    ArePiecesSetUp = false; //pieces not setup initially
    pieceToPlace = NULL; //no piece to place initially

    ThisClientSocket = new TCPsocket(); //connect later in ready button

    //initialize mainmenu attributes
    LoggedIn = false;
    waitingLoginText = new QGraphicsTextItem(QString(""));

    //initialize game variables
    player1NameText = new QGraphicsTextItem(QString(""));
    player2NameText = new QGraphicsTextItem(QString(""));

    //initialize other Pieces variables
    countF = -1;
    count1 = -1;
    count2 = -1;
    count3 = -1;
    count4 = -1;
    count5 = -1;
    count6 = -1;
    count7 = -1;
    count8 = -1;
    count9 = -1;
    count10 = -1;
    countB = -1;

}

QPointF Game::toSceneCoord(int Col, int Row){
     return QPointF(Col*55+155, Row*55 + 23);
}

void Game::start(){
    //clear the screen
    scene->clear();

    //test code TODO REMOVE LATER
    Gameboard = new Board();
    Gameboard->placePieces(150 + 5, 18 + 5);
    drawGUI();
    createInitialPieces(thisPlayerColor); //start pieces with given color by the server
}

void Game::ready(){
    if (ArePiecesPlaced() == true){
        qDebug() << "player ready and pieces placed";
        SetPiecesMessage();
        qDebug() << MessageToSend;
        qDebug() << "Message length: " << MessageToSend.length();

        ThisClientSocket->writeData(MessageToSend);
    }
}

void Game::setUpDefaultPositions(){
    for (size_t i = 0, n = ThisPlayerPieces.size(); i < n; i++){
        int xDefaultPosition = 155 + 55*(i%10);
        int yDefaultPosition = 23 + 55*6 + 55*(i/10);
        ThisPlayerPieces[i]->setPos(xDefaultPosition, yDefaultPosition);
        ThisPlayerPieces[i]->setZValue(1);
        ThisPlayerPieces[i]->setIsPlaced(true); //piece is now placed
        pieceToPlace = NULL; //piece already placed
    }
}

void Game::loginGame(){
    ThisClientSocket->Connect(); //connect to socket(if not connected)
    qDebug() << "1";

    //create middle panel
    int xPanel = this->width()/2 - 300/2;
    int yPanel = 100;
    drawPanel(xPanel, yPanel, 300, 430, QColor(237, 214, 181), 1);

    qDebug() << "1";

    //create the title text
    titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = yPanel;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);

    //Create retry connection button
    retryConButton = new Button(QString("Retry"), 50, 25);
    int xretryConButton = this->width()/2 - 300/2 + 5;
    int yretryConButton = titleText->pos().y() + titleText->boundingRect().height() - 10;
    retryConButton->setPos(xretryConButton, yretryConButton);
    connect(retryConButton, SIGNAL(clicked()), ThisClientSocket, SLOT(Connect()));
    scene->addItem(retryConButton);

    //Create Connection state text
    int xConStateText = xretryConButton + retryConButton->boundingRect().width() + 5;
    int yConStateText = yretryConButton;
    ThisClientSocket->ConnectionToServerStateText->setPos(xConStateText, yConStateText);
    scene->addItem(ThisClientSocket->ConnectionToServerStateText);


    qDebug() << "2";

    //Create Login Name text
    loginNameText = new QGraphicsTextItem(QString("Account Name: "));
    QFont loginFont("Sans Serif 10", 10); //set font and size
    loginFont.setBold(true);
    loginNameText->setFont(loginFont);
    int xLoginNameText = xPanel + 5;
    int yLoginNameText = yConStateText + ThisClientSocket->ConnectionToServerStateText->boundingRect().height() + 5;
    loginNameText->setPos(xLoginNameText, yLoginNameText);
    scene->addItem(loginNameText);

    qDebug() << "3";

    //create textBox to write Login Name
    loginNameTextbox = new Textbox(15, 15, true, 170, 25);
    int xloginNameTextbox = xLoginNameText + loginNameText->boundingRect().width() + 2;
    int yloginNameTextbox = yLoginNameText;
    loginNameTextbox->setPos(xloginNameTextbox, yloginNameTextbox);
    scene->addItem(loginNameTextbox);

    qDebug() << "4";

    //Create Login Password text
    loginPasswordText = new QGraphicsTextItem(QString("Password: "));
    loginPasswordText->setFont(loginFont);
    int xLoginPasswordText = xPanel + 5;
    int yLoginPasswordText = yloginNameTextbox + loginNameTextbox->boundingRect().height() + 5;
    loginPasswordText->setPos(xLoginPasswordText, yLoginPasswordText);
    scene->addItem(loginPasswordText);

    qDebug() << "5";

    //create textBox to write Login Password
    loginPasswordTextbox = new Textbox(15, 15, false, 170, 25);
    int xloginPasswordTextbox = xloginNameTextbox;
    int yloginPasswordTextbox = yLoginPasswordText;
    loginPasswordTextbox->setPos(xloginPasswordTextbox, yloginPasswordTextbox);
    scene->addItem(loginPasswordTextbox);

    qDebug() << "6";

    //create the register button
    registerButton = new Button(QString("Register Account"), 141, 50);
    int xrButton = xPanel + 6;
    int yrButton = yLoginPasswordText + loginPasswordTextbox->boundingRect().height() + 5;
    registerButton->setPos(xrButton, yrButton);
    connect(registerButton, SIGNAL(clicked()), this, SLOT(waitForRegister()));
    scene->addItem(registerButton);

    qDebug() << "7";

    //create the login button
    loginButton = new Button(QString("Login"), 141, 50);
    int xlButton = xPanel + 6 + registerButton->boundingRect().width() + 6;
    int ylButton = yLoginPasswordText + loginPasswordTextbox->boundingRect().height() + 5;
    loginButton->setPos(xlButton, ylButton);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(waitForLogin()));
    scene->addItem(loginButton);

    qDebug() << "8";

    //create the quit button
    quitButton = new Button(QString("Quit"), 200, 50);
    int xqButton = this->width()/2 - quitButton->boundingRect().width()/2;
    int yqButton = 453;
    quitButton->setPos(xqButton, yqButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    qDebug() << "9";
}

void Game::waitForLogin(){
    if (loginNameTextbox->getWriten().size() > 4 && loginPasswordTextbox->getWriten().size() > 4){
        thisPlayerName = loginNameTextbox->getWriten();
        SetLoginMessage(true, thisPlayerName, loginPasswordTextbox->getWriten());
        //create message to send
        qDebug() << "Send new Login Message: " << MessageToSend;
        ThisClientSocket->writeData(MessageToSend);
    }
    else{
        QList<QGraphicsItem *> itemsInScene = scene->items();
        for(QGraphicsItem *item : itemsInScene) { //to avoid removing text from scene if it isnt there in the first place (avoid crash)
            if(item == waitingLoginText) {
                scene->removeItem(waitingLoginText);
                break;
            }
        }
        waitingLoginText->setPlainText(QString("Name/Password have 5-15 digits"));
        int xLogin = this->width()/2 - waitingLoginText->boundingRect().width()/2;
        int yLogin = 453 - 75 - 50;
        waitingLoginText->setPos(xLogin, yLogin);
        scene->addItem(waitingLoginText); //add join to scene after clicking "login" if necessary
    }
}

void Game::waitForRegister(){
    if (loginNameTextbox->getWriten().size() > 4 && loginPasswordTextbox->getWriten().size() > 4){
        SetLoginMessage(false, loginNameTextbox->getWriten(), loginPasswordTextbox->getWriten());
        //create message to send
        qDebug() << "Send new Login Message: " << MessageToSend;
        ThisClientSocket->writeData(MessageToSend);
    }
    else{
        QList<QGraphicsItem *> itemsInScene = scene->items();
        for(QGraphicsItem *item : itemsInScene) { //to avoid removing text from scene if it isnt there in the first place (avoid crash)
            if(item == waitingLoginText) {
                scene->removeItem(waitingLoginText);
                break;
            }
        }
        waitingLoginText->setPlainText(QString("Registered Name/Password needs to have 5-15 digits"));
        int xLogin = this->width()/2 - waitingLoginText->boundingRect().width()/2;
        int yLogin = 453 - 75 - 50;
        waitingLoginText->setPos(xLogin, yLogin);
        scene->addItem(waitingLoginText); //add join to scene after clicking "login" if necessary
    }
}

void Game::displayMainMenu(){
    //clean unnecessary items
    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items) {
        if(item != titleText || item != ngButton || item != jgButton || item != instButton || item != quitButton) {
            scene->removeItem(item);
        }
    }


    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);


    //create the title text
    titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 100;
    titleText->setPos(xTitle, yTitle);
    titleText->setZValue(1);
    scene->addItem(titleText);

    //create the New Game button
    ngButton = new Button(QString("New Game"), 200, 50);
    int xngButton = this->width()/2 - ngButton->boundingRect().width()/2;
    int yngButton = 100 + titleText->boundingRect().height() + 25;
    ngButton->setPos(xngButton, yngButton);
    ngButton->setZValue(1);
    connect(ngButton, SIGNAL(clicked()), this, SLOT(createRoom()));
    scene->addItem(ngButton);

    //create the Join Game button
    jgButton = new Button(QString("Join Game"), 200, 50);
    int xjgButton = xngButton;
    int yjgButton = yngButton + 75;
    jgButton->setPos(xjgButton, yjgButton);
    jgButton->setZValue(1);
    connect(jgButton, SIGNAL(clicked()), this, SLOT(joinRoom()));
    scene->addItem(jgButton);

    //create the instructions button
    instButton = new Button(QString("Instructions"), 200, 50);
    int xinstButton = xngButton;
    int yinstButton = yjgButton + 75;
    instButton->setPos(xinstButton, yinstButton);
    instButton->setZValue(1);
    scene->addItem(instButton);

    //create the quit button
    quitButton = new Button(QString("Quit"), 200, 50);
    int xqButton = xngButton;
    int yqButton = yinstButton + 75;
    quitButton->setPos(xqButton, yqButton);
    quitButton->setZValue(1);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}


void Game::displayGameOver(){
    //clean unnecessary items
    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items) {
        if(item != titleText || item != ngButton || item != jgButton || item != instButton || item != quitButton) {
            scene->removeItem(item);
        }
    }

    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);

    //create the title text
    titleText = new QGraphicsTextItem(QString("GAME OVER"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 100;
    titleText->setPos(xTitle, yTitle);
    titleText->setZValue(1);
    scene->addItem(titleText);

    //create the Back button
    backButton = new Button(QString("Back"), 200, 50);
    int xbackButton = this->width()/2 - backButton->boundingRect().width()/2;
    int ybackButton = 100 + titleText->boundingRect().height() + 25;
    backButton->setPos(xbackButton, ybackButton);
    backButton->setZValue(1);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);
}

void Game::joinRoom(){
    ThisClientSocket->Connect(); //connect to socket(if not connected)

    //clean unnecessary items
    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items) {
        if(item != titleText && item != retryConButton && item != roomText && item != roomTextbox && item != joinRoomButton && item != backButton ) {
            scene->removeItem(item);
        }
    }

    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);

    //Create retry connection button
    retryConButton = new Button(QString("Retry"), 50, 25);
    int xretryConButton = this->width()/2 - 300/2 + 5;
    int yretryConButton = titleText->pos().y() + titleText->boundingRect().height() - 10;
    retryConButton->setPos(xretryConButton, yretryConButton);
    connect(retryConButton, SIGNAL(clicked()), ThisClientSocket, SLOT(Connect()));
    scene->addItem(retryConButton);

    //Create Connection state text
    int xConStateText = xretryConButton + retryConButton->boundingRect().width() + 5;
    int yConStateText = yretryConButton;
    ThisClientSocket->ConnectionToServerStateText->setPos(xConStateText, yConStateText);
    scene->addItem(ThisClientSocket->ConnectionToServerStateText);

    //Create Room name text
    roomText = new QGraphicsTextItem(QString("Join Room name:"));
    QFont roomFont("Sans Serif 10", 20); //set font and size
    roomText->setFont(roomFont);
    int xRoom = this->width()/2 - roomText->boundingRect().width()/2;
    int yRoom = titleText->pos().y() + titleText->boundingRect().height() + 10;
    roomText->setPos(xRoom, yRoom);
    scene->addItem(roomText);

    //create textBox to write Room number
    roomTextbox = new Textbox(6, 15, true, 90, 25); //QString "number" does nothing, change later
    int xRoomTextBox = xRoom;
    int yRoomTextBox = yRoom + 50;
    roomTextbox->setPos(xRoomTextBox, yRoomTextBox);
    scene->addItem(roomTextbox);

    //create Join Room button
    createRoomButton = new Button(QString("Join"), 100, 25);
    int xcreateRoomButton = xRoomTextBox + roomTextbox->boundingRect().width() + 5;
    int ycreateRoomButton = yRoomTextBox;
    createRoomButton->setPos(xcreateRoomButton, ycreateRoomButton);
    disconnect(createRoomButton);
    connect(createRoomButton, SIGNAL(clicked()), this, SLOT(joinRoomClicked()));
    scene->addItem(createRoomButton);

    //create waitingJoinText
    waitingJoinText = new QGraphicsTextItem(QString(""));
    int yJoin = yRoomTextBox + roomTextbox->boundingRect().height() + 25;
    waitingJoinText->setY(yJoin); //dont write or add to scene yet

    //create back to menu button
    backButton = new Button(QString("Back"), 100, 50);
    int xbackButton = this->width()/2 - 300/2 + 190;
    int ybackButton = 530 - 50 - 10;
    backButton->setPos(xbackButton, ybackButton);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);
}

void Game::joinRoomClicked(){
    if (roomTextbox->getWriten() != ""){
        roomNumber = roomTextbox->getWriten();
        //create message to send
        SetJoinRoomMessage(roomNumber);
        qDebug() << "Send join Room Message: " << MessageToSend;
        ThisClientSocket->writeData(MessageToSend);
        waitingJoinText->setPlainText(QString("..."));
        int xJoin = this->width()/2 - waitingJoinText->boundingRect().width()/2;
        waitingJoinText->setX(xJoin);
        scene->addItem(waitingJoinText); //add join to scene after clicking "create"
    }
}


void Game::createRoom(){
    ThisClientSocket->Connect(); //connect to socket(if not connected)

    //clean unnecessary items
    QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem *item : items) {
        if(item != titleText && item != retryConButton && item != roomText && item != roomTextbox && item != createRoomButton && item != waitingJoinText && item != backButton ) {
            scene->removeItem(item);
        }
    }

    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);

    //Create retry connection button
    retryConButton = new Button(QString("Retry"), 50, 25);
    int xretryConButton = this->width()/2 - 300/2 + 5;
    int yretryConButton = titleText->pos().y() + titleText->boundingRect().height() - 10;
    retryConButton->setPos(xretryConButton, yretryConButton);
    connect(retryConButton, SIGNAL(clicked()), ThisClientSocket, SLOT(Connect()));
    scene->addItem(retryConButton);

    //Create Connection state text
    int xConStateText = xretryConButton + retryConButton->boundingRect().width() + 5;
    int yConStateText = yretryConButton;
    ThisClientSocket->ConnectionToServerStateText->setPos(xConStateText, yConStateText);
    scene->addItem(ThisClientSocket->ConnectionToServerStateText);

    //Create Room name text
    roomText = new QGraphicsTextItem(QString("Room name:"));
    QFont roomFont("Sans Serif 10", 20); //set font and size
    roomText->setFont(roomFont);
    int xRoom = this->width()/2 - roomText->boundingRect().width()/2;
    int yRoom = titleText->pos().y() + titleText->boundingRect().height() + 10;
    roomText->setPos(xRoom, yRoom);
    scene->addItem(roomText);

    //create textBox to write Room number
    roomTextbox = new Textbox(6, 15, true, 90, 25); //QString "number" does nothing, change later
    int xRoomTextBox = xRoom;
    int yRoomTextBox = yRoom + 50;
    roomTextbox->setPos(xRoomTextBox, yRoomTextBox);
    scene->addItem(roomTextbox);

    //create Create Room button
    createRoomButton = new Button(QString("Create"), 100, 25);
    int xcreateRoomButton = xRoomTextBox + roomTextbox->boundingRect().width() + 5;
    int ycreateRoomButton = yRoomTextBox;
    createRoomButton->setPos(xcreateRoomButton, ycreateRoomButton);
    disconnect(createRoomButton);
    connect(createRoomButton, SIGNAL(clicked()), this, SLOT(createRoomClicked()));
    scene->addItem(createRoomButton);

    //create waitingJoinText
    waitingJoinText = new QGraphicsTextItem(QString(""));
    int yJoin = yRoomTextBox + roomTextbox->boundingRect().height() + 25;
    waitingJoinText->setY(yJoin); //dont write or add to scene yet

    //create back to menu button
    backButton = new Button(QString("Back"), 100, 50);
    int xbackButton = this->width()/2 - 300/2 + 190;
    int ybackButton = 530 - 50 - 10;
    backButton->setPos(xbackButton, ybackButton);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);
}

void Game::createRoomClicked(){
    if (roomTextbox->getWriten() != ""){
        roomNumber = roomTextbox->getWriten();
        //create message to send
        SetRoomMessage(roomNumber);
        qDebug() << "Send new Room Message: " << MessageToSend;
        ThisClientSocket->writeData(MessageToSend);
        waitingJoinText->setPlainText(QString("..."));
        int xJoin = this->width()/2 - waitingJoinText->boundingRect().width()/2;
        waitingJoinText->setX(xJoin);
        scene->addItem(waitingJoinText); //add join to scene after clicking "create"
    }
}


QString Game::getTurn(){
    return Turn;
}

void Game::setTurn(QString player){
    //change QString
    Turn = player;

    //change QGraphicsTextItem
    TurnText->setPlainText(QString("Whose turn: ") + player);
}

void Game::pickUpPiece(Piece* piece){
    //picks up the specified card
    if (getArePiecesSetUp() == false){
        if (piece->getOwner() == thisPlayerColor && piece->getOwner() == getTurn() && pieceToPlace == NULL){ //if piece to pick up belongs to this client's player, it is this player's turn and and no piece picked up yet
            piece->setZValue(10);
            pieceToPlace = piece;
            return;
        }
    }
    else{ //if pieces already setup, change original position; else original position is in the side panel; cant pick up piece on the side panel(now its the graveyard)
        if (piece->getOwner() == thisPlayerColor && piece->getOwner() == getTurn() && piece->pos().x() > 150 && pieceToPlace == NULL){ //if piece to pick up belongs to this client's player, it is this player's turn and and no piece picked up yet
            piece->setZValue(10);
            pieceToPlace = piece;
            piece->originalPos = piece->pos();
            piece->originalZ = piece->zValue();
            return;
        }
    }
}

void Game::placePiece(Piece *pieceToReplace){ //piece is ON TOP of board's empty pieces
    qDebug() << "Pieces placed? -> " << ArePiecesPlaced();
    qDebug() << "Unplaced pieces list size-> " << ThisPlayerPieces[39];


    if (getArePiecesSetUp() == false){    //if pieces not setup yet, a piece can be placed anywhere in the stup area
        if(pieceToReplace->pos().y() >= 18 + 5 + 6*55){ //if in initial squares
            //replace specified piece with pieceToPlace
            pieceToPlace->setPos(pieceToReplace->pos());
            pieceToPlace->setZValue(1);
            pieceToPlace->setIsPlaced(true); //piece is now placed
            pieceToPlace = NULL; //piece already placed
        }
    }
    else if(getArePiecesSetUp() == true){ //if GAME already started(pieces are set up)
        if(pieceToPlace->getRank() == "2"){ //scout
            qDebug() << "atempting to place scout";
            bool legalMove = false; //the scout may be moving diagonally, so legalmove = false
            int iSrcCol = pieceToPlace->getiX();
            int iSrcRow = pieceToPlace->getiY();
            int iDestCol = pieceToReplace->getiX();
            int iDestRow = pieceToReplace->getiY();
            qDebug() << "Source Square: " << iSrcRow << "||" << iSrcCol;
            qDebug() << "Destination Square: " << iDestRow << "||" << iDestCol;
            if(iSrcRow == iDestRow && iSrcCol == iDestCol){ //if placing piece in same place, it is set, but no "new move" message is sent to server
                pieceToPlace->setPos(pieceToReplace->pos());
                pieceToPlace->setZValue(1);
                pieceToPlace->setIsPlaced(true);
                pieceToPlace = NULL;
            }
            else if((iSrcRow == iDestRow) && (iSrcCol != iDestCol)){ // if moving in a row(same row; increasing or decreasing column)
                legalMove = true; //if it is moving in a row, legalMove starts as true
                //check if trajectory is clean of other pieces/water
                int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;   //1 if increasing in column, -1 if decreasing in column
                qDebug() << "moving in a row";
                for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {  //check column trajectory
                    QPointF position = toSceneCoord(iCheckCol, iSrcRow);
                    qDebug() << "Position checking: " << position;
                    QList<QGraphicsItem*> itemsAtPosition = scene->items(position);
                    for(QGraphicsItem* item : itemsAtPosition) { //check items at position
                        Piece* piece = dynamic_cast<Piece*>(item);
                        if(piece != nullptr) { // The item is a Piece object
                            if (piece->getOwner() != QString("NOONE") || piece->getOwner() == QString("GAME") ){ //check squares are not empty (if it is a piece with owner or water)
                                legalMove = false; //if not empty, scout doesnt move, change legalmove to false
                            }
                        }
                    }
                }
            }
            else if((iSrcRow != iDestRow) && (iSrcCol == iDestCol)){ // if moving in a column(same column; increasing or decreasing row)
                legalMove = true; //if it is moving in a column, legalMove starts as true
                //check if trajectory is clean of other pieces/water
                qDebug() << "moving in a column";
                int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1; //1 if increasing in row, -1 if decreasing in row
                for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {  //check row trajectory
                    QPointF position = toSceneCoord(iSrcCol, iCheckRow);
                    qDebug() << "Position checking: " << position;
                    QList<QGraphicsItem*> itemsAtPosition = scene->items(position);
                    for(QGraphicsItem* item : itemsAtPosition) { //check items at position
                        Piece* piece = dynamic_cast<Piece*>(item);
                        if(piece != nullptr) { // The item is a Piece object
                            if (piece->getOwner() != QString("NOONE") || piece->getOwner() == QString("GAME") ){ //check squares are not empty (if it is a piece with owner or water)
                                legalMove = false; //if not empty, scout doesnt move
                            }
                        }
                    }
                }
            }
            if (legalMove == true){ //if it was a legal move, place piece
                pieceToPlace->setPos(pieceToReplace->pos());
                pieceToPlace->setZValue(1);
                pieceToPlace->setIsPlaced(true);
                pieceToPlace->originalPos = pieceToPlace->pos();
                pieceToPlace->originalZ = pieceToPlace->zValue();
                pieceMoveMessage(iSrcRow, iSrcCol, iDestRow, iDestCol);
                atackingPiece = pieceToPlace;
                defendingPiece = pieceToReplace;
                pieceToPlace = NULL;
            }
        }
        //Other pieces movement:
        else if(pieceToPlace->getRank() != "2" && pieceToPlace->getRank() != "B" && pieceToPlace->getRank() != "F"){ //other pieces
            qDebug() << "atempting to place simple moving piece";
            bool legalMove = false; //the piece may be moving diagonally, so legalmove = false
            int iSrcCol = pieceToPlace->getiX();
            int iSrcRow = pieceToPlace->getiY();
            int iDestCol = pieceToReplace->getiX();
            int iDestRow = pieceToReplace->getiY();
            qDebug() << "Source Square: " << iSrcRow << "||" << iSrcCol;
            qDebug() << "Destination Square: " << iDestRow << "||" << iDestCol;
            if(iSrcRow == iDestRow && iSrcCol == iDestCol){ //if placing piece in same place, it is set, but no "new move" message is sent to server
                pieceToPlace->setPos(pieceToReplace->pos());
                pieceToPlace->setZValue(1);
                pieceToPlace->setIsPlaced(true);
                pieceToPlace = NULL;
            }
            else if (iSrcRow == iDestRow) { //if moving in a row (same row, +-1 column)
                legalMove = true; //if it is moving in a row, legalMove starts as true
                if ( abs(iSrcCol - iDestCol) != 1 ){ //if moving 1 square exactly
                    legalMove = false;
                }
            }
            else if (iDestCol == iSrcCol) {  //if moving in a column (same column, +-1 row)
                legalMove = true; //if it is moving in a column, legalMove starts as true
                if ( abs(iSrcRow - iDestRow) != 1 ){ //if moving 1 square exactly
                    legalMove = false;
                }
            }
            if (legalMove == true){ //if it was a legal move, place piece
                pieceToPlace->setPos(pieceToReplace->pos());
                pieceToPlace->setZValue(1);
                pieceToPlace->setIsPlaced(true);
                pieceToPlace->originalPos = pieceToPlace->pos();
                pieceToPlace->originalZ = pieceToPlace->zValue();
                pieceMoveMessage(iSrcRow, iSrcCol, iDestRow, iDestCol);
                atackingPiece = pieceToPlace;
                defendingPiece = pieceToReplace;
                pieceToPlace = NULL;
            }
        }
        //make it the next players turn if piece was placed and ArePiecesSetup == true
        if (pieceToPlace == NULL){
            nextPlayersTurn(); //1move per play
        }
    }
}

void Game::nextPlayersTurn(){
    if (getTurn() == QString("REDPLAYER")){
        setTurn("BLUEPLAYER");
    }
    else if (getTurn() == QString("BLUEPLAYER")){
        setTurn("REDPLAYER");
    }
}

//void Game::removeFromPanel(Piece *piece, QString player){
//    if (player == QString("REDPLAYER")){
//        //remove from red player
//        ThisPlayerPieces.removeAll(piece);
//    }
//    if (player == QString("BLUEPLAYER")){
//        //remove from blue player
//        blueUnplacedPieces.removeAll(piece);
//    }

//}

void Game::mouseMoveEvent(QMouseEvent* event){
    //if there is a piecetoplace, then make it follow the mouse
    if (pieceToPlace){
        pieceToPlace->setPos(event->pos().x() + 3, event->pos().y() + 3); //piece follow the mouse
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    //make right click return pieceToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (pieceToPlace){
            pieceToPlace->setPos(pieceToPlace->originalPos);
            pieceToPlace->setZValue(pieceToPlace->originalZ);
            pieceToPlace = NULL;
            return;
        }
    }
    //else, normal behaviour:
    QGraphicsView:: mousePressEvent(event);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    //draws panelat specified location with specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    panel->setZValue(0);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //set panel color
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity); //set transparency of panel
    scene->addItem(panel);
}

void Game::drawGUI(){
    //draw left panel
    drawPanel(0, 0, 145, scene->height(), QColor(237, 214, 181), 1);

    //draw right panel
    drawPanel(scene->width() - 145, 0, 145, scene->height(), QColor(237, 214, 181), 1);

    //place player 1 text
    player1NameText->setPlainText(thisPlayerName);
    player1NameText->setPos(145/2 - player1NameText->boundingRect().width()/2, 0);
    scene->addItem(player1NameText);

    //place player 2 text
    player2NameText->setPlainText(otherPlayerName);
    player2NameText->setPos(scene->width() - 145/2 - player2NameText->boundingRect().width()/2 , 0);
    scene->addItem(player2NameText);

    //place whose turn text
    TurnText = new QGraphicsTextItem(); //turn is changed in setTurn function
    setTurn(thisPlayerColor);
    int xTurnText = scene->width()/2 - TurnText->boundingRect().width()/2;
    int yTurnText = 0;
    TurnText->setPos(xTurnText, yTurnText);
    scene->addItem(TurnText);

    //place last battle information
    lastBattleText = new QGraphicsTextItem(); //initialize text
    lastBattleText->setPlainText(QString("Last Battle: "));
    vsBattleText = new QGraphicsTextItem(); //initialize text
    vsBattleText->setPlainText(QString("VS"));
    demoThisPiece = new Piece(); //initialize demo pieces
    demoOtherPiece = new Piece();
    if (thisPlayerColor == QString("REDPLAYER")){ //set respective owners(color)
        demoThisPiece->setOwner(QString("DEMORED")); //set respective owners(color)
        demoOtherPiece->setOwner(QString("DEMOBLUE"));
    }
    else{
        demoThisPiece->setOwner(QString("DEMOBLUE"));
        demoOtherPiece->setOwner(QString("DEMORED"));
    }
    demoThisPiece->setIsPlaced(true);
    demoOtherPiece->setIsPlaced(true);

    int xBattleText = xTurnText + TurnText->boundingRect().width() + 20;
    int yBattleText = yTurnText;
    lastBattleText->setPos(xBattleText,yBattleText);
    scene->addItem(lastBattleText);

    demoThisPiece->setRect(0, 0, 18, 18);
    demoThisPiece->rankText->setPos(9 - demoThisPiece->rankText->boundingRect().width()/2, 9 - demoThisPiece->rankText->boundingRect().height()/2);
    int xThisDemo = xBattleText + lastBattleText->boundingRect().width() + 2;
    int yThisDemo = 2;
    demoThisPiece->setPos(xThisDemo,yThisDemo);
    scene->addItem(demoThisPiece);

    int xVsText = xThisDemo + demoThisPiece->sceneBoundingRect().width() + 2;
    int yVsText = yBattleText;
    vsBattleText->setPos(xVsText,yVsText);
    scene->addItem(vsBattleText);

    demoOtherPiece->setRect(0, 0, 18, 18);
    demoOtherPiece->rankText->setPos(9 - demoOtherPiece->rankText->boundingRect().width()/2, 9 - demoOtherPiece->rankText->boundingRect().height()/2);
    int xOtherDemo = xVsText + vsBattleText->boundingRect().width() + 2;
    int yOtherDemo = yThisDemo;
    demoOtherPiece->setPos(xOtherDemo,yOtherDemo);
    scene->addItem(demoOtherPiece);

    //place Ready button
    Button* readyButton = new Button(QString("Ready"), 100, 50);
    int xreadyButton = scene->width() - 150/2 - readyButton->boundingRect().width()/2;
    int yreadyButton = scene->height() - 5 - readyButton->boundingRect().height();
    readyButton->setPos(xreadyButton, yreadyButton);
    connect(readyButton, SIGNAL(clicked()), this, SLOT(ready()));
    scene->addItem(readyButton);

    //place Default Piece Positions button
    Button* defaultPositionsButton = new Button(QString("Default"), 100, 50);
    int xdefaultButton = 150/2 - defaultPositionsButton->boundingRect().width()/2;
    int ydefaultButton = scene->height() - 5 - defaultPositionsButton->boundingRect().height();
    defaultPositionsButton->setPos(xdefaultButton, ydefaultButton);
    connect(defaultPositionsButton, SIGNAL(clicked()), this, SLOT(setUpDefaultPositions()));
    scene->addItem(defaultPositionsButton);

}

void Game::createNewPiece(QString player, QString pieceRank){
    Piece* initialpiece = new Piece();  //Create piece
    initialpiece->setRank(pieceRank);
    //add card to proper list
    if (player == thisPlayerColor){
        initialpiece->setIsPlaced(false);
        initialpiece->setOwner(player);     //Set to player(red or blue)
        ThisPlayerPieces.append(initialpiece);
    }
    else {
        initialpiece->setIsPlaced(true);
        initialpiece->setOwner(player);
        OtherPlayerPieces.append(initialpiece);
    }
}

void Game::createInitialPieces(QString player){
    //create this player's pieces
    createNewPiece(player, "F");  //create 1 Flag
    createNewPiece(player, "1");  //create 1 Spy
    for (size_t i = 0; i < 8; i++){
        createNewPiece(player, "2"); //create 8 Scouts
    }
    for (size_t i = 0; i < 5; i++){
        createNewPiece(player, "3"); //create 5 Miners
    }
    for (size_t i = 0; i < 4; i++){
        createNewPiece(player, "4"); //create 4 Sergeants
    }
    for (size_t i = 0; i < 4; i++){
        createNewPiece(player, "5"); //create 4 Lieutenants
    }
    for (size_t i = 0; i < 4; i++){
        createNewPiece(player, "6"); //create 4 Captains
    }
    for (size_t i = 0; i < 3; i++){
        createNewPiece(player, "7"); //create 3 Majors
    }
    for (size_t i = 0; i < 2; i++){
        createNewPiece(player, "8"); //create 2 Colonels
    }
    createNewPiece(player, "9"); //create 1 General
    createNewPiece(player, "10"); //create 1 Marshal
    for (size_t i = 0; i < 6; i++){
        createNewPiece(player, "B"); //create 6 Bombs
    }
    //create other player's pieces:
    QString otherPlayer;
    if (player == QString("REDPLAYER")){
        otherPlayer = QString("BLUEPLAYER");
    }
    else if (player == QString("BLUEPLAYER")){
        otherPlayer = QString("REDPLAYER");
    }
    for (size_t i = 0; i < 40; i++){
        createNewPiece(otherPlayer,"N");
    }

    drawThisPieces();
}


void Game::drawThisPieces(){
    //traverse through list of pieces and draw them on side panels

    //remove all of this players pieces from the scene(to avoid overlap)
    for (size_t i = 0, n = ThisPlayerPieces.size(); i < n; i++){
        scene->removeItem(ThisPlayerPieces[i]);
    }

    //draw this player's pieces
    for (size_t i = 0, n = ThisPlayerPieces.size(); i < n; i++){
        Piece* initialpiece = ThisPlayerPieces[i];
        //draw Flag
        if (i == 0){
            initialpiece->setPos(50/3 + i*(50 + 50/3), 25);
            initialpiece->setZValue(i + 1);
            otherPositionF = initialpiece->pos();
        }
        //draw Spy
        else if (i == 1){
            initialpiece->setPos(50/3 + i*(50 + 50/3), 25);
            initialpiece->setZValue(i + 1);
            otherPosition1 = initialpiece->pos();
        }
        //draw Scouts
        else if (2 <= i && i < 10){
            initialpiece->setPos(50/3, 75 + 10 + (i - 2)*5 );
            initialpiece->setZValue(i - 1);
            if (i == 2){
                otherPosition2 = initialpiece->pos();
            }
        }
        //draw Miners
        else if (10 <= i && i < 15){
            initialpiece->setPos(2*50/3 + 50, 75 + 10 + (i - 10)*5 );
            initialpiece->setZValue(i - 9);
            if (i == 10){
                otherPosition3 = initialpiece->pos();
            }
        }
        //draw Sergeants
        else if (15 <= i && i < 19){
            initialpiece->setPos(50/3, 170 + 10 + (i - 15)*5 );
            initialpiece->setZValue(i - 14);
            if (i == 15){
                otherPosition4 = initialpiece->pos();
            }
        }
        //draw Lieutenants
        else if (19 <= i && i < 23){
            initialpiece->setPos(2*50/3 + 50, 170 + 10 + (i - 19)*5 );
            initialpiece->setZValue(i - 18);
            if (i == 19){
                otherPosition5 = initialpiece->pos();
            }
        }
        //draw Captains
        else if (23 <= i && i < 27){
            initialpiece->setPos(50/3, 245 + 10 + (i - 23)*5 );
            initialpiece->setZValue(i - 22);
            if (i == 23){
                otherPosition6 = initialpiece->pos();
            }
        }
        //draw Majors
        else if (27 <= i && i < 30){
            initialpiece->setPos(2*50/3 + 50, 245 + 10 + (i - 27)*5 );
            initialpiece->setZValue(i - 26);
            if (i == 27){
                otherPosition7 = initialpiece->pos();
            }
        }
        //draw Colonels
        else if (30 <= i && i < 32){
            initialpiece->setPos(50/3, 315 + 10 + (i - 30)*5 );
            initialpiece->setZValue(i - 29);
            if (i == 30){
                otherPosition8 = initialpiece->pos();
            }
        }
        //draw General
        else if (i == 32){
            initialpiece->setPos(2*50/3 + 50, 315 + 10 + (i - 32)*5 );
            initialpiece->setZValue(i - 31);
            otherPosition9 = initialpiece->pos();
        }
        //draw Marshal
        else if (i == 33){
            initialpiece->setPos(50/3, 375 + 25 + (i - 33)*5 );
            initialpiece->setZValue(i - 32);
            otherPosition10 = initialpiece->pos();
        }
        //draw Bombs
        else if (34 <= i && i < 40){
            initialpiece->setPos(2*50/3 + 50, 375 + 25 + (i - 34)*5 );
            initialpiece->setZValue(i - 33);
            if (i == 34){
                otherPositionB = initialpiece->pos();
            }
        }
        initialpiece->originalPos = initialpiece->pos();
        initialpiece->originalZ = initialpiece->zValue();
        initialpiece->originalPanelPos = initialpiece->pos();
        initialpiece->originalPanelZ = initialpiece->zValue();
        scene->addItem(initialpiece);
    }
}

void Game::drawOtherPieces(){
    //draw other player's pieces
    for (size_t i = 0; i < 40; i++){
        Piece* initialpiece = OtherPlayerPieces[i];
        qDebug() << 150 + 5 + 55*(i%10) << "||" << 18 + 5 + 55*(i/10);
        initialpiece->setPos(150 + 5 + 55*(i%10), 18 + 5 + 55*(i/10));
        initialpiece->setZValue(0);
        initialpiece->originalPos = initialpiece->pos();
        initialpiece->originalZ = initialpiece->zValue();
        initialpiece->originalPanelPos = initialpiece->pos();
        initialpiece->originalPanelZ = initialpiece->zValue();
        initialpiece->setVisible(false);
        scene->addItem(initialpiece);
    }
}

bool Game::getArePiecesSetUp(){
    return ArePiecesSetUp;
}

bool Game::ArePiecesPlaced(){
    for (size_t i = 0, n = ThisPlayerPieces.size(); i < n; i++){
        if (ThisPlayerPieces[i]->pos().x() < 150){ //if at least 1 piece still in panel, return false
            return false;
        }
    }
    //if no piece in panel, return true
    return true;
}

void Game::SetLoginMessage(bool existingAcc, QString name, QString password){
    if(existingAcc == true){
        MessageToSend = QString("LOGIN");
    }
    else{
        MessageToSend = QString("REGIS");
    }
    MessageToSend.append(name + QString("|"));
    MessageToSend.append(password);
}

void Game::SetPiecesMessage(){ //Initial Pieces setup message to send to the server
    MessageToSend = QString("SETUP");
    for (size_t i = 0, n = ThisPlayerPieces.size(); i < n; i++){
        int xPosition = (ThisPlayerPieces[i]->pos().x() - 155)/55;
        int yPosition = (ThisPlayerPieces[i]->pos().y() - 23)/55;
        QString thisRank = ThisPlayerPieces[i]->getRank();
        if (thisRank.length() == 1){
            thisRank = QString("0") + thisRank;
        }
        MessageToSend.append(QString::number(yPosition) + QString::number(xPosition) + thisRank);
    }
}

void Game::pieceMoveMessage(int srcRow, int srcCol, int destRow, int destCol){
    QString message = QString("MOVEP"); //MOVE PIECE
    message.append(QString::number(srcRow) + QString::number(srcCol) + QString::number(destRow) + QString::number(destCol)); //add source and destination square
    ThisClientSocket->writeData(message);
}

void Game::SetRoomMessage(QString room){
    MessageToSend = QString("SETRO"); //SET ROOM
    MessageToSend.append(room + "|");
}

void Game::SetJoinRoomMessage(QString room){
    MessageToSend = QString("JOIRO"); //JOIN ROOM
    MessageToSend.append(room + "|");
}

//determines what to do with data from server
void Game::setDataReceived(QString data){
    qDebug() << "Received from server: " << data;
    QString identifier = data.left(5);
    if (identifier == QString("LOGFA")){ //login failed
        waitingLoginText->setPlainText(QString("Your Name or Password do not match")   );
        int xLogin = this->width()/2 - waitingLoginText->boundingRect().width()/2;
        int yLogin = 453 - 75 - 50;
        waitingLoginText->setPos(xLogin, yLogin);
        scene->addItem(waitingLoginText); //add join to scene after clicking "login" if necessary
    }
    else if (identifier == QString("LOGCO")){ //login completed
        LoggedIn = true;
        displayMainMenu();
    }
    else if (identifier == QString("REGFA")){ //register failed
        waitingLoginText->setPlainText(QString("Account with that name already exists")   );
        int xLogin = this->width()/2 - waitingLoginText->boundingRect().width()/2;
        int yLogin = 453 - 75 - 50;
        waitingLoginText->setPos(xLogin, yLogin);
        scene->addItem(waitingLoginText); //add join to scene after clicking "login" if necessary
    }
    else if (identifier == QString("REGCO")){ //register completed
        waitingLoginText->setPlainText(QString("Account created sucessfuly")   );
        int xLogin = this->width()/2 - waitingLoginText->boundingRect().width()/2;
        int yLogin = 453 - 75 - 50;
        waitingLoginText->setPos(xLogin, yLogin);
        scene->addItem(waitingLoginText); //add join to scene after clicking "login" if necessary
    }
    else if (identifier == QString("ROCSU")){ //Room creation sucessfull
        roomNumber = roomTextbox->getWriten();
        qDebug() << "Room set to: " << roomNumber;
        waitingJoinText->setPlainText(QString("Room Created, waiting for another player to join"));
        int xJoin = this->width()/2 - waitingJoinText->boundingRect().width()/2;
        waitingJoinText->setX(xJoin);
    }
    else if (identifier == QString("ROCFA")){ //Room creation failed
        waitingJoinText->setPlainText(QString("Room already exists, choose another"));
        int xJoin = this->width()/2 - waitingJoinText->boundingRect().width()/2;
        waitingJoinText->setX(xJoin);
    }
    else if(identifier == QString("JOIFA")){ //Join failed
        waitingJoinText->setPlainText(QString("Room you are trying to join does not exist"));
        int xJoin = this->width()/2 - waitingJoinText->boundingRect().width()/2;
        waitingJoinText->setX(xJoin);
    }
    else if(identifier == QString("SETRE")){ //Set this player as red, and save other player's name
        thisPlayerColor = QString("REDPLAYER");
        int datalength = data.size();
        otherPlayerName = data.mid(5, datalength-5);
        start();
    }
    else if(identifier == QString("SETBL")){ //Set this player as blue, and save other player's name
        thisPlayerColor = QString("BLUEPLAYER");
        int datalength = data.size();
        otherPlayerName = data.mid(5, datalength-5);
        start();
    }
    else if(identifier == QString("START")){ //START game, red starts
        drawOtherPieces(); //show unranked enemy pieces(because we dont know the ranks
        ArePiecesSetUp = true;
        setTurn(QString("REDPLAYER"));
    }
    else if(identifier == QString("MOVAR")){ //MOVE atack response
        int datalength = data.size();
        QString atackResponse = data.mid(5, 5 - datalength);
        atackMoveResponse(atackResponse);
    }
    else if(identifier == QString("MOVDR")){ //MOVE defense response
        int datalength = data.size();
        QString defenseResponse = data.mid(5, 5 - datalength);
        defenseMoveResponse(defenseResponse);
    }
}

void Game::atackMoveResponse(QString response){
    QString result = response.at(0);
    QString otherRank = response.mid(1,2);
    if (otherRank.at(0) == QString("0")){ //if it is not a 10, ignore the first character of the rank( a 0)
        otherRank = otherRank.at(1);
    }
    qDebug() << "atacking piece atacked a " << otherRank;
    if (result == "W"){ //atacking moved piece wins
        if (otherRank != "N"){ //if not moving to empty square
            placeOtherDefeatedPiece(defendingPiece, otherRank);
            defendingPiece->setRank(otherRank);
            defendingPiece->setVisible(true); //rank is visible when dead
        }
    }
    else if (result == "D"){ //both pieces loose
        placeOtherDefeatedPiece(defendingPiece, otherRank);
        defendingPiece->setRank(otherRank);
        defendingPiece->setVisible(true); //rank is visible when dead
        atackingPiece->setPos(atackingPiece->originalPanelPos);
        atackingPiece->setZValue(atackingPiece->originalPanelZ);
    }
    else if (result == "L"){ //atacking piece dies
        atackingPiece->setPos(atackingPiece->originalPanelPos);
        atackingPiece->setZValue(atackingPiece->originalPanelZ);
    }
    QString thisRank = atackingPiece->getRank();
    if (thisRank != "N" && otherRank != "N"){ //if there was a battle, update demo pieces
        demoThisPiece->setRank(thisRank);
        demoOtherPiece->setRank(otherRank);
    }
    defendingPiece = NULL;
    atackingPiece = NULL;
}

void Game::defenseMoveResponse(QString response){
    QString result = response.at(0);
    int SrcRow = response.at(1).digitValue();
    int SrcCol = response.at(2).digitValue();
    int DestRow = response.at(3).digitValue();
    int DestCol = response.at(4).digitValue();
    QString otherRank = response.right(2);
    if (otherRank.at(0) == QString("0")){ //if it is not a 10, ignore the first character of the rank( a 0)
        otherRank = otherRank.at(1);
    }
    qDebug() << otherRank << " atacking piece atacked a defending piece ";
    QPointF position;
    QList<QGraphicsItem*> itemsAtPosition;
    //find atacking piece
    position = toSceneCoord(SrcCol, SrcRow);
    qDebug() << "Position checking for atacking piece: " << position;
    itemsAtPosition = scene->items(position);
    for(QGraphicsItem* item : itemsAtPosition) { //check items at position
        Piece* piece = dynamic_cast<Piece*>(item);
        if(piece != nullptr) { // The item is a Piece object
            qDebug() << "this piece has owner: " << piece->getOwner();
            if (piece->getOwner() != QString("NOONE") && piece->getOwner() != thisPlayerColor ){ //it must be an enemy piece
                atackingPiece = piece;
            }
        }
    }
    //find defending piece
    position = toSceneCoord(DestCol, DestRow);
    qDebug() << "Position checking for defending piece: " << position;
    itemsAtPosition = scene->items(position);
    for(QGraphicsItem* item : itemsAtPosition) { //check items at position
        Piece* piece = dynamic_cast<Piece*>(item);
        if(piece != nullptr) { // The item is a Piece object
            qDebug() << "this piece has owner: " << piece->getOwner();
            if (piece->getOwner() == thisPlayerColor ){ //if it is this players piece
                defendingPiece = piece;
            }
            else if (piece->getOwner() == QString("NOONE") && defendingPiece == NULL){ //if there is no player piece, it is a empty piece
                defendingPiece = piece;
            }
        }
    }
    atackingPiece->setPos(defendingPiece->pos());
    atackingPiece->originalPos = atackingPiece->pos();
    QString thisRank = defendingPiece->getRank();
    //determine which piece survives
    if (result == "L"){ //atacking moved piece looses
        if (thisRank != "N"){ //if not moving to empty square
            placeOtherDefeatedPiece(atackingPiece, otherRank);
            atackingPiece->setRank(otherRank);
            atackingPiece->setVisible(true); //rank is visible when dead
        }
    }
    else if (result == "D"){ //both pieces loose
        placeOtherDefeatedPiece(atackingPiece, otherRank);
        atackingPiece->setRank(otherRank);
        atackingPiece->setVisible(true); //rank is visible when dead
        defendingPiece->setPos(defendingPiece->originalPanelPos);
        defendingPiece->setZValue(defendingPiece->originalPanelZ);
    }
    else if (result == "W"){ //atacking moved piece wins
        defendingPiece->setPos(defendingPiece->originalPanelPos);
        defendingPiece->setZValue(defendingPiece->originalPanelZ);
    }
    if (thisRank != "N" && otherRank != "N"){ //if there was a battle, update demo pieces
        demoThisPiece->setRank(thisRank);
        demoOtherPiece->setRank(otherRank);
    }
    defendingPiece = NULL;
    atackingPiece = NULL;
    nextPlayersTurn(); //now it is this player's turn
}


void Game::placeOtherDefeatedPiece(Piece *piece, QString rank){
    int StartingX = scene->width() - 145;
    if (rank == QString("1")){
        count1+=1;
        piece->setPos(StartingX + otherPosition1.x(),otherPosition1.y());
        piece->setZValue(1);
    }
    else if (rank == QString("2")){
        count2+=1;
        piece->setPos(StartingX + otherPosition2.x(),otherPosition2.y() + count2*5);
        piece->setZValue(1+count2);
    }
    else if (rank == QString("3")){
        count3+=1;
        piece->setPos(StartingX + otherPosition3.x(),otherPosition3.y() + count3*5);
        piece->setZValue(1+count3);
    }
    else if (rank == QString("4")){
        count4+=1;
        piece->setPos(StartingX + otherPosition4.x(),otherPosition4.y() + count4*5);
        piece->setZValue(1+count4);
    }
    else if (rank == QString("5")){
        count5+=1;
        piece->setPos(StartingX + otherPosition5.x(),otherPosition5.y() + count5*5);
        piece->setZValue(1+count5);
    }
    else if (rank == QString("6")){
        count6+=1;
        piece->setPos(StartingX + otherPosition6.x(),otherPosition6.y() + count6*5);
        piece->setZValue(1+count6);
    }
    else if (rank == QString("7")){
        count2+=1;
        piece->setPos(StartingX + otherPosition7.x(),otherPosition7.y() + count7*5);
        piece->setZValue(1+count7);
    }
    else if (rank == QString("8")){
        count8+=1;
        piece->setPos(StartingX + otherPosition8.x(),otherPosition8.y() + count8*5);
        piece->setZValue(1+count8);
    }
    else if (rank == QString("9")){
        count9+=1;
        piece->setPos(StartingX + otherPosition9.x(),otherPosition9.y() + count9*5);
        piece->setZValue(1+count9);
    }
    else if (rank == QString("10")){
        count10+=1;
        piece->setPos(StartingX + otherPosition2.x(),otherPosition2.y() + count10*5);
        piece->setZValue(1+count10);
    }
    else if (rank == QString("B")){
        countB+=1;
        piece->setPos(StartingX + otherPositionB.x(),otherPositionB.y() + countB*5);
        piece->setZValue(1+countB);
    }
}




