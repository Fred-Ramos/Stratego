#include "Game.h"
#include "Button.h"

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
    ArePiecesSetUp = false; //pieces not setup initially
    pieceToPlace = NULL; //no piece to place initially
}

void Game::start(){
    //clear the screen
    scene->clear();

    //test code TODO REMOVE LATER
    board = new Board();
    board->placePieces(150 + 5, 18 + 5);
    drawGUI();
    createInitialPieces();
}

void Game::displayMainMenu(){
    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 100;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);

    //create the new Game button
    Button* ngButton = new Button(QString("New Game"));
    int xngButton = this->width()/2 - ngButton->boundingRect().width()/2;
    int yngButton = 100 + titleText->boundingRect().height() + 25;
    ngButton->setPos(xngButton, yngButton);
    connect(ngButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(ngButton);

    //create the new Game button
    Button* jgButton = new Button(QString("Join Game"));
    int xjgButton = this->width()/2 - jgButton->boundingRect().width()/2;
    int yjgButton = yngButton + 75;
    jgButton->setPos(xjgButton, yjgButton);
    connect(jgButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(jgButton);

    //create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int xqButton = this->width()/2 - quitButton->boundingRect().width()/2;
    int yqButton = yjgButton + 75;
    quitButton->setPos(xqButton, yqButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
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
    qDebug() << "entered pickup function";
    qDebug() << pieceToPlace; //CHECK if null
    qDebug() << getTurn();
    //picks up the specified card
    if (piece->getOwner() == getTurn() && pieceToPlace == NULL){ //if piece to pick up belongs to player and no piece picked up yet
        piece->setZValue(10);
        qDebug() << "correct player picking";
        pieceToPlace = piece;
        originalPos = piece->pos();
        return;
    }
}

void Game::placePiece(Piece *pieceToReplace){ //piece is ON TOP of board's empty pieces
    if (getArePiecesSetUp() == false){    //if pieces not setup yet
        if(getTurn() == QString("REDPLAYER") && pieceToReplace->pos().y() >= 18 + 5 + 6*55){ //if redturn,
            //replace specified piece with pieceToPlace
            pieceToPlace->setPos(pieceToReplace->pos());
            pieceToPlace->setZValue(1);
            pieceToPlace->setIsPlaced(true); //piece is now placed
            removeFromPanel(pieceToPlace, getTurn());
            pieceToPlace = NULL; //piece already placed
        }
        else if(getTurn() == QString("BLUEPLAYER") && pieceToReplace->pos().y() <= 18 + 5 + 3*55){ //else if blueturn
            //replace specified piece with pieceToPlace
            pieceToPlace->setPos(pieceToReplace->pos());
            pieceToPlace->setZValue(1);
            pieceToPlace->setIsPlaced(true); //piece is now placed
            removeFromPanel(pieceToPlace, getTurn());
            pieceToPlace = NULL; //piece already placed
        }
    }
    //make it the next players turn if piece was placed
    if (pieceToPlace == NULL){
        nextPlayersTurn();
    }
}

void Game::nextPlayersTurn(){
    if (getTurn() == QString("REDPLAYER")){
        qDebug() << "changed to blue turn";
        setTurn("BLUEPLAYER");
    }
    else{
        qDebug() << "changed to red turn";
        setTurn("REDPLAYER");
    }
}

void Game::removeFromPanel(Piece *piece, QString player){
    if (player == QString("REDPLAYER")){
        //remove from red player
        redUnplacedPieces.removeAll(piece);
    }
    if (player == QString("BLUEPLAYER")){
        //remove from blue player
        blueUnplacedPieces.removeAll(piece);
    }

}

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
            pieceToPlace->setPos(originalPos);
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
    drawPanel(0, 0, 145, scene->height(), QColor(237, 214, 181), 2);

    //draw right panel
    drawPanel(scene->width() - 145, 0, 145, scene->height(), QColor(237, 214, 181), 2);

    //place red player text
    QGraphicsTextItem* rplayer = new QGraphicsTextItem("Red Player pieces");
    rplayer->setPos(145/2 - rplayer->boundingRect().width()/2, 0);
    scene->addItem(rplayer);

    //place blue player text
    QGraphicsTextItem* bplayer = new QGraphicsTextItem("Blue Player pieces");
    bplayer->setPos(scene->width() - 145/2 - bplayer->boundingRect().width()/2 , 0);
    scene->addItem(bplayer);

    //place whose turn text
    TurnText = new QGraphicsTextItem(); //turn is changed in setTurn function
    setTurn(QString("REDPLAYER"));
    TurnText->setPos(scene->width()/2 - TurnText->boundingRect().width()/2, 0);
    scene->addItem(TurnText);
}

void Game::createNewPiece(QString player){
    Piece* initialpiece = new Piece();  //Create piece
    initialpiece->setOwner(player);     //Set to player(red or blue)
    initialpiece->setIsPlaced(false);
    //add card to proper list
    if (player == QString("REDPLAYER")){
        redUnplacedPieces.append(initialpiece);
    }
    else if (player == QString("BLUEPLAYER")){
        blueUnplacedPieces.append(initialpiece);
    }
    //draw the pieces
    drawPieces();
}

void Game::createInitialPieces(){
    //create red player's pieces
    for (size_t i = 0; i < 5; i++){
        createNewPiece(QString("REDPLAYER"));
    }
    //create blue player's pieces
    for (size_t i = 0; i < 5; i++){
        createNewPiece(QString("BLUEPLAYER"));
    }
    drawPieces();
}

void Game::drawPieces(){
    //traverse through list of pieces and draw them on side panels

    //remove all of redplayer pieces from the scene(to avoid overlap)
    for (size_t i = 0, n = redUnplacedPieces.size(); i < n; i++){
        scene->removeItem(redUnplacedPieces[i]);
    }
    //remove all of blueplayer pieces from the scene
    for (size_t i = 0, n = blueUnplacedPieces.size(); i < n; i++){
        scene->removeItem(blueUnplacedPieces[i]);
    }

    //draw red player's pieces
    for (size_t i = 0, n = redUnplacedPieces.size(); i < n; i++){
        Piece* initialpiece = redUnplacedPieces[i];
        initialpiece->setPos(5, 23 + i*55 );
        scene->addItem(initialpiece);
    }
    //draw blue player's pieces
    for (size_t i = 0, n = blueUnplacedPieces.size(); i < n; i++){
        Piece* initialpiece = blueUnplacedPieces[i];
        initialpiece->setPos(scene->width() - 140, 23 + i*55 );
        scene->addItem(initialpiece);
    }
}

bool Game::getArePiecesSetUp(){
    return ArePiecesSetUp;
}
