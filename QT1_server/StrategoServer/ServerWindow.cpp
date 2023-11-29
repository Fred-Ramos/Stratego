#include "ServerWindow.h"
#include "tcpserver.h"
#include "Button.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

#include <QDebug>

extern TCPServer* gameServer;      //global variable

ServerWindow::ServerWindow(QWidget *parent){ //constructor
    //Set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(855, 573);

    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 855, 573); //scene same size of the screen
    setScene(scene);

    ConnectionStateText = new QGraphicsTextItem();
    setConnectionState("nothing");
    dataReceivedText = new QGraphicsTextItem();
    setDataReceived(" ");
}

void ServerWindow::setConnectionState(QString state){
    //change QGraphicsTextItem
    ConnectionStateText->setPlainText(QString("Connection state: ") + state);
}

void ServerWindow::setDataReceived(QString data){
    //change QGraphicsTextItem
    dataReceivedText->setPlainText(QString("Last data received: ") + data);
}

void ServerWindow::displayVariables(){
    scene->clear();
    //create middle panel
    drawPanel(this->width()/2 - 300/2, 100, 300, 430, QColor(237, 214, 181), 1);

    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 100;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);

    //create the server text
    QGraphicsTextItem* serverText = new QGraphicsTextItem(QString("Server"));
    QFont serverFont("Sans Serif 10", 15); //set font and size
    serverText->setFont(serverFont);
    int xServer = xTitle + 10;
    int yServer = 100 + titleText->boundingRect().height() - 35;
    serverText->setPos(xServer, yServer);
    scene->addItem(serverText);

    //display connectionstate
    ConnectionStateText->setPos(scene->width()/2 - ConnectionStateText->boundingRect().width()/2, yServer + 25);
    scene->addItem(ConnectionStateText);

    dataReceivedText->setPos(scene->width()/2 - ConnectionStateText->boundingRect().width()/2, yServer + 50);
    scene->addItem(dataReceivedText);


    //create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int xqButton = this->width()/2 - quitButton->boundingRect().width()/2;
    int yqButton = 530 - quitButton->boundingRect().height() - 25;
    quitButton->setPos(xqButton, yqButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void ServerWindow::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    //draws panelat specified location with specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //set panel color
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity); //set transparency of panel
    scene->addItem(panel);
}


