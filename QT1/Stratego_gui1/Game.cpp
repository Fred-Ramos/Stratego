#include "Game.h"
#include "Button.h"

#include <QGraphicsTextItem>
#include <QBrush>

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

    //create the play button
    Button* playButton = new Button(QString("New Game"));
    int xButton = this->width()/2 - playButton->boundingRect().width()/2;
    int yButton = 100 + titleText->boundingRect().height() + 25;
    playButton->setPos(xButton, yButton);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    //create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int xqButton = this->width()/2 - quitButton->boundingRect().width()/2;
    int yqButton = yButton + 75;
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
    setTurn(QString("Red Player"));
    TurnText->setPos(scene->width()/2 - TurnText->boundingRect().width()/2, 0);
    scene->addItem(TurnText);
}

void Game::createNewPiece(QString player){
    Piece* initialpiece = new Piece();  //Create piece
    initialpiece->setOwner(player);     //Set to player(red or blue)

    //add card to proper list
    if (player == QString("REDPLAYER")){
        redPieces.append(initialpiece);
    }
    else if (player == QString("BLUEPLAYER")){
        bluePieces.append(initialpiece);
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
    for (size_t i = 0, n = redPieces.size(); i < n; i++){
        scene->removeItem(redPieces[i]);
    }
    //remove all of blueplayer pieces from the scene
    for (size_t i = 0, n = bluePieces.size(); i < n; i++){
        scene->removeItem(bluePieces[i]);
    }

    //draw red player's pieces
    for (size_t i = 0, n = redPieces.size(); i < n; i++){
        Piece* initialpiece = redPieces[i];
        initialpiece->setPos(5, 23 + i*55 );
        scene->addItem(initialpiece);
    }
    //draw blue player's pieces
    for (size_t i = 0, n = bluePieces.size(); i < n; i++){
        Piece* initialpiece = bluePieces[i];
        initialpiece->setPos(scene->width() - 140, 23 + i*55 );
        scene->addItem(initialpiece);
    }

}
