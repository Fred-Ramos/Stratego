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


}

void Game::start(){
    //clear the screen
    scene->clear();

    //test code TODO REMOVE LATER
    Gameboard = new Board();
    Gameboard->placePieces(150 + 5, 18 + 5);
    drawGUI();
    createInitialPieces(QString("UNASSIGNED"));
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
    for (size_t i = 0, n = UnassignedUnplacedPieces.size(); i < n; i++){
        int xDefaultPosition = 155 + 55*(i%10);
        int yDefaultPosition = 23 + 55*6 + 55*(i/10);
        UnassignedUnplacedPieces[i]->setPos(xDefaultPosition, yDefaultPosition);
        UnassignedUnplacedPieces[i]->setZValue(1);
        UnassignedUnplacedPieces[i]->setIsPlaced(true); //piece is now placed
        pieceToPlace = NULL; //piece already placed
    }
}

void Game::loginGame(){
    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);


    //create the title text
    titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 100;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);


    //create the quit button
    quitButton = new Button(QString("Quit"), 200, 50);
    int xqButton = this->width()/2 - quitButton->boundingRect().width()/2;;
    int yqButton = 453;
    quitButton->setPos(xqButton, yqButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayMainMenu(){
    //scene->clear();
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
    scene->addItem(titleText);

    //create the New Game button
    ngButton = new Button(QString("New Game"), 200, 50);
    int xngButton = this->width()/2 - ngButton->boundingRect().width()/2;
    int yngButton = 100 + titleText->boundingRect().height() + 25;
    ngButton->setPos(xngButton, yngButton);
    connect(ngButton, SIGNAL(clicked()), this, SLOT(createRoom()));
    scene->addItem(ngButton);

    //create the Join Game button
    jgButton = new Button(QString("Join Game"), 200, 50);
    int xjgButton = xngButton;
    int yjgButton = yngButton + 75;
    jgButton->setPos(xjgButton, yjgButton);
    connect(jgButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(jgButton);

    //create the instructions button
    instButton = new Button(QString("Instructions"), 200, 50);
    int xinstButton = xngButton;
    int yinstButton = yjgButton + 75;
    instButton->setPos(xinstButton, yinstButton);
    scene->addItem(instButton);

    //create the quit button
    quitButton = new Button(QString("Quit"), 200, 50);
    int xqButton = xngButton;
    int yqButton = yinstButton + 75;
    quitButton->setPos(xqButton, yqButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::createRoom(){
    ThisClientSocket->Connect(); //connect to socket(if not connected)
    scene->removeItem(ngButton);
    scene->removeItem(jgButton);
    scene->removeItem(instButton);
    scene->removeItem(quitButton);

    qDebug() << "1";
    //Create retry connection button
    retryConButton = new Button(QString("Retry"), 50, 25);
    int xretryConButton = this->width()/2 - 300/2 + 5;
    int yretryConButton = titleText->pos().y() + titleText->boundingRect().height() - 10;
    retryConButton->setPos(xretryConButton, yretryConButton);
    connect(retryConButton, SIGNAL(clicked()), ThisClientSocket, SLOT(Connect()));
    scene->addItem(retryConButton);

    qDebug() << "2";
    //Create Connection state text
    int xConStateText = xretryConButton + retryConButton->boundingRect().width() + 5;
    int yConStateText = yretryConButton;
    ThisClientSocket->ConnectionToServerStateText->setPos(xConStateText, yConStateText);
    scene->addItem(ThisClientSocket->ConnectionToServerStateText);
    qDebug() << "3";

    //Create Room name text
    roomText = new QGraphicsTextItem(QString("Room name:"));
    QFont roomFont("Sans Serif 10", 20); //set font and size
    roomText->setFont(roomFont);
    int xRoom = this->width()/2 - roomText->boundingRect().width()/2;
    int yRoom = titleText->pos().y() + titleText->boundingRect().height() + 10;
    roomText->setPos(xRoom, yRoom);
    scene->addItem(roomText);
    qDebug() << "4";

    //create textBox to write Room number
    roomTextbox = new Textbox(QString(""), 90, 25); //QString "number" does nothing, change later
    int xRoomTextBox = xRoom;
    int yRoomTextBox = yRoom + 50;
    roomTextbox->setPos(xRoomTextBox, yRoomTextBox);
    scene->addItem(roomTextbox);
    qDebug() << "5";

    //create Create Room button
    createRoomButton = new Button(QString("Create"), 100, 25);
    int xcreateRoomButton = xRoomTextBox + roomTextbox->boundingRect().width() + 5;
    int ycreateRoomButton = yRoomTextBox;
    createRoomButton->setPos(xcreateRoomButton, ycreateRoomButton);
    connect(createRoomButton, SIGNAL(clicked()), this, SLOT(waitForJoin()));
    scene->addItem(createRoomButton);
    qDebug() << "6";

    //create waitingJoinText
    waitingJoinText = new QGraphicsTextItem();
    int yJoin = yRoomTextBox + roomTextbox->boundingRect().height() + 25;
    waitingJoinText->setY(yJoin); //dont write or add to scene yet

    qDebug() << "4";

    //create back to menu button
    backButton = new Button(QString("Back"), 100, 50);
    int xbackButton = this->width()/2 - 300/2 + 190;
    int ybackButton = 530 - 50 - 10;
    backButton->setPos(xbackButton, ybackButton);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(backButton);
    qDebug() << "7";
}

void Game::waitForJoin(){
    if (roomTextbox->roomNumber != ""){
        //create message to send
        SetRoomMessage(roomTextbox->roomNumber);
        qDebug() << "Send new Room Message: " << MessageToSend;
        ThisClientSocket->writeData(MessageToSend);
        waitingJoinText->setPlainText(QString("Waiting for another player to join..."));
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
    if (piece->getOwner() == getTurn() && pieceToPlace == NULL){ //if piece to pick up belongs to player and no piece picked up yet
        piece->setZValue(10);
        pieceToPlace = piece;
        if (getArePiecesSetUp() == true){ //if pieces already setup, change original position; else original position is in the side panel
           piece->originalPos = piece->pos();
            piece->originalZ = piece->zValue();
        }
        return;
    }
}

void Game::placePiece(Piece *pieceToReplace){ //piece is ON TOP of board's empty pieces
    qDebug() << "Pieces placed? -> " << ArePiecesPlaced();
    qDebug() << "Unassigned list size-> " << UnassignedUnplacedPieces[39];
    if (getArePiecesSetUp() == false){    //if pieces not setup yet
        if(pieceToReplace->pos().y() >= 18 + 5 + 6*55){ //if in initial squares
            //replace specified piece with pieceToPlace
            pieceToPlace->setPos(pieceToReplace->pos());
            pieceToPlace->setZValue(1);
            pieceToPlace->setIsPlaced(true); //piece is now placed
            //removeFromPanel(pieceToPlace, getTurn());
            pieceToPlace = NULL; //piece already placed
        }
    }
    //make it the next players turn if piece was placed
    if (pieceToPlace == NULL){
        //nextPlayersTurn(); COMMENTED, CHANGE LATER
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
//        UnassignedUnplacedPieces.removeAll(piece);
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

    //place red player text
    QGraphicsTextItem* rplayer = new QGraphicsTextItem("Player 1 pieces");
    rplayer->setPos(145/2 - rplayer->boundingRect().width()/2, 0);
    scene->addItem(rplayer);

    //place blue player text
    QGraphicsTextItem* bplayer = new QGraphicsTextItem("Player 2 pieces");
    bplayer->setPos(scene->width() - 145/2 - bplayer->boundingRect().width()/2 , 0);
    scene->addItem(bplayer);

    //place whose turn text
    TurnText = new QGraphicsTextItem(); //turn is changed in setTurn function
    setTurn(QString("UNASSIGNED"));
    TurnText->setPos(scene->width()/2 - TurnText->boundingRect().width()/2, 0);
    scene->addItem(TurnText);

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
    initialpiece->setOwner(player);     //Set to player(red or blue)
    initialpiece->setRank(pieceRank);
    initialpiece->setIsPlaced(false);
    //add card to proper list
    if (player == QString("UNASSIGNED")){
        UnassignedUnplacedPieces.append(initialpiece);
    }
    //draw the pieces
    drawPieces();
}

void Game::createInitialPieces(QString player){
    //create unAsigned player's pieces
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
    drawPieces();
    }
}

void Game::drawPieces(){
    //traverse through list of pieces and draw them on side panels

    //remove all of unassigned pieces from the scene(to avoid overlap)
    for (size_t i = 0, n = UnassignedUnplacedPieces.size(); i < n; i++){
        scene->removeItem(UnassignedUnplacedPieces[i]);
    }

    //draw red player's pieces
    for (size_t i = 0, n = UnassignedUnplacedPieces.size(); i < n; i++){
        Piece* initialpiece = UnassignedUnplacedPieces[i];
        //draw Flag and Spy
        if (i < 2){
            initialpiece->setPos(50/3 + i*(50 + 50/3), 25);
            initialpiece->setZValue(i + 1);
        }
        //draw Scouts
        else if (2 <= i && i < 10){
            initialpiece->setPos(50/3, 75 + 10 + (i - 2)*5 );
            initialpiece->setZValue(i - 1);
        }
        //draw Miners
        else if (10 <= i && i < 15){
            initialpiece->setPos(2*50/3 + 50, 75 + 10 + (i - 10)*5 );
            initialpiece->setZValue(i - 9);
        }
        //draw Sergeants
        else if (15 <= i && i < 19){
            initialpiece->setPos(50/3, 170 + 10 + (i - 15)*5 );
            initialpiece->setZValue(i - 14);
        }
        //draw Lieutenants
        else if (19 <= i && i < 23){
            initialpiece->setPos(2*50/3 + 50, 170 + 10 + (i - 19)*5 );
            initialpiece->setZValue(i - 18);
        }
        //draw Captains
        else if (23 <= i && i < 27){
            initialpiece->setPos(50/3, 245 + 10 + (i - 23)*5 );
            initialpiece->setZValue(i - 22);
        }
        //draw Majors
        else if (27 <= i && i < 30){
            initialpiece->setPos(2*50/3 + 50, 245 + 10 + (i - 27)*5 );
            initialpiece->setZValue(i - 26);
        }
        //draw Colonels
        else if (30 <= i && i < 32){
            initialpiece->setPos(50/3, 315 + 10 + (i - 30)*5 );
            initialpiece->setZValue(i - 29);
        }
        //draw General
        else if (i == 32){
            initialpiece->setPos(2*50/3 + 50, 315 + 10 + (i - 32)*5 );
            initialpiece->setZValue(i - 31);
        }
        //draw Marshal
        else if (i == 33){
            initialpiece->setPos(50/3, 375 + 25 + (i - 33)*5 );
            initialpiece->setZValue(i - 32);
        }
        //draw Bombs
        else if (34 <= i && i < 40){
            initialpiece->setPos(2*50/3 + 50, 375 + 25 + (i - 34)*5 );
            initialpiece->setZValue(i - 33);
        }
        initialpiece->originalPos = initialpiece->pos();
        initialpiece->originalZ = initialpiece->zValue();
        scene->addItem(initialpiece);

    }

    //draw blue player's pieces
//    for (size_t i = 0, n = blueUnplacedPieces.size(); i < n; i++){
//        Piece* initialpiece = blueUnplacedPieces[i];
//        initialpiece->setPos(scene->width() - 140, 23 + i*15 );
//        initialpiece->originalPos = initialpiece->pos();
//        initialpiece->setZValue(i);
//        initialpiece->originalZ = initialpiece->zValue();
//        scene->addItem(initialpiece);
    //    }
}

bool Game::ArePiecesPlaced(){
    for (size_t i = 0, n = UnassignedUnplacedPieces.size(); i < n; i++){
        if (UnassignedUnplacedPieces[i]->pos().x() < 150){ //if at least 1 piece still in panel, return false
            return false;
        }
    }
    //if no piece in panel, return true
    return true;
}

void Game::SetPiecesMessage(){ //Initial Pieces setup message to send to the server
    MessageToSend = QString("SETUP");
    for (size_t i = 0, n = UnassignedUnplacedPieces.size(); i < n; i++){
        int xPosition = (UnassignedUnplacedPieces[i]->pos().x() - 155)/55;
        int yPosition = (UnassignedUnplacedPieces[i]->pos().y() - 23)/55;
        QString thisRank = UnassignedUnplacedPieces[i]->getRank();
        if (thisRank.length() == 1){
            thisRank = QString("0") + thisRank;
        }
        MessageToSend.append(QString::number(xPosition) + QString::number(yPosition) + thisRank);
    }
}

void Game::SetRoomMessage(QString room){
    MessageToSend = QString("SETRO");
    MessageToSend.append(room + "X");
}


bool Game::getArePiecesSetUp(){
    return ArePiecesSetUp;
}
