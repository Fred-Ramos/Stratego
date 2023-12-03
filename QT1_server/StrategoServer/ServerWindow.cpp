#include "ServerWindow.h"
#include "tcpserver.h"
#include "player.h"
#include "Button.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

#include <QDir>
#include <QStandardPaths>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QDebug>

extern TCPServer* gameServer;      //global variable

ServerWindow::ServerWindow(QWidget *parent){ //constructor
    //Set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(855, 573);

    //set up directory to save files
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); //Get path to documents folder
    QDir dir(documentsPath + "/StrategoGame"); //folder to look for
    if (!dir.exists()){
        dir.mkpath("."); //if folder doesnt exist in this machine, create one
    }

    // Create the database inside the directory
    database = QSqlDatabase::addDatabase("QSQLITE"); //create database to store passwords(doesnt overwrite previous database, if there is one)
    database.setDatabaseName(dir.filePath("StrategoGame.db"));

    // Check database connection
    if (database.open()) {
        qDebug() << "Database: connection ok";
    }
    else {
        qDebug() << "Error: connection with database fail";
    }

    //create user table in database
    QSqlQuery query(database);
    query.exec("CREATE TABLE IF NOT EXISTS Users (username TEXT, password TEXT)");


    //delete usernames and passwords if needed:
    query.exec("DELETE FROM Users");




    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 855, 573); //scene same size of the screen
    setScene(scene);

    ConnectionStateText = new QGraphicsTextItem();
    setConnectionState("nothing");
    dataReceivedText = new QGraphicsTextItem(QString(""));
    dataReceivedIpPortText = new QGraphicsTextItem(QString(""));
}

void ServerWindow::setConnectionState(QString state){
    //change QGraphicsTextItem
    ConnectionStateText->setPlainText(QString("Connection state: ") + state);
}

void ServerWindow::setDataReceived(QTcpSocket* socket, QString data){
    QString connectionIP = socket->peerAddress().toString();              //see source ip
    QString connectionSourcePort = QString::number(socket->peerPort());   //see source port

    qDebug() << "New data from client: " << connectionIP << " from port: " << connectionSourcePort;

    QString ResponseMessage;

    //change QGraphicsTextItem
    dataReceivedText->setPlainText(QString("Last data received: ") + data);
    dataReceivedIpPortText->setPlainText(QString("IP: ") + connectionIP + QString(" | Source Port: ") + connectionSourcePort);

    //determine response to the client
    if (data.left(5) == QString("REGIS")){
        //read pretended username and password
        int changeIndex = data.indexOf("|");
        QString thisUsername = data.mid(5, changeIndex - 5); //from position 5, read "changeIndex - 5" characters
        QString thisPassword = data.mid(changeIndex + 1, data.size() - 1 - changeIndex);
        qDebug() << thisUsername;
        qDebug() << thisPassword;
        ResponseMessage = setRegisterResponse(thisUsername, thisPassword);
        if (ResponseMessage == QString("LOGCO")){
            //create player for this server session
            Player* player = new Player(thisUsername, connectionIP, connectionSourcePort);
            Players.append(player); //add player to list
        }
        gameServer->writeToClient(socket, ResponseMessage);
    }
    else if (data.mid(0,5) == QString("LOGIN")){
        //read pretended username and password
        int changeIndex = data.indexOf("|");
        QString thisUsername = data.mid(5, changeIndex - 5); //from position 5, read "changeIndex - 5" characters
        QString thisPassword = data.mid(changeIndex + 1, data.size() - 1 - changeIndex);
        qDebug() << thisUsername;
        qDebug() << thisPassword;
        ResponseMessage = setLoginResponse(thisUsername, thisPassword); //run new login function
        gameServer->writeToClient(socket, ResponseMessage);
    }
    else if (data.mid(0,5) == QString("SETRO")){ //set room
        for (Player* player : Players) {
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game room
                setRoomResponse(player, data);
            }
        }
    }


}

void ServerWindow::displayVariables(){
    scene->clear();
    //create middle panel
    drawPanel(this->width()/2 - 825/2, 5, 825, 530, QColor(237, 214, 181), 1);

    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Stratego"));
    QFont titleFont("GothicI", 50); //set font and size
    titleText->setFont(titleFont);
    int xTitle = this->width()/2 - titleText->boundingRect().width()/2;
    int yTitle = 5;
    titleText->setPos(xTitle, yTitle);
    scene->addItem(titleText);

    //create the server text
    QGraphicsTextItem* serverText = new QGraphicsTextItem(QString("Server"));
    QFont serverFont("Sans Serif 10", 15); //set font and size
    serverText->setFont(serverFont);
    int xServer = xTitle + 10;
    int yServer = 5 + titleText->boundingRect().height() - 35;
    serverText->setPos(xServer, yServer);
    scene->addItem(serverText);

    //display connectionstate
    int xCon = this->width()/2 - 825/2 + 5;
    int yCon = yServer + 25;
    ConnectionStateText->setPos(xCon, yCon);
    QFont infoFont("Segoe", 6); //set font and size
    ConnectionStateText->setFont(infoFont);
    scene->addItem(ConnectionStateText);

    //display last recieved data
    int xDataText = this->width()/2 - 825/2 + 5;
    int yDataText = yCon + 15;
    dataReceivedText->setPos(xDataText, yDataText);
    dataReceivedText->setFont(infoFont);
    scene->addItem(dataReceivedText);

    //data received ip and source port
    int xIpPortText = xDataText;
    int yIpPortText = yDataText + 15;
    dataReceivedIpPortText->setPos(xIpPortText, yIpPortText);
    dataReceivedIpPortText->setFont(infoFont);
    scene->addItem(dataReceivedIpPortText);


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

QString ServerWindow::setLoginResponse(QString receivedUsername, QString receivedPassword){
    //check if username and password exist and match
    QSqlQuery query(database);                                                                     //Create query
    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");      //prepares a SELECT command to select all rows from the Users table
    query.bindValue(":username", receivedUsername);                                                //bind pretended username
    query.bindValue(":password", receivedPassword);                                                //bind pretended password
    query.exec();                                                                                  //execute query

    QString message;
    if (query.next()) { //there is a row with matched username and password
        qDebug() << "username/password correct"; // The username and password exist and match in the database.
        message = "LOGCO"; //login correct
        //if login correct, create new player with this name
    }
    else {
        qDebug() << "username/password incorrect" ; // The username and password do not exist or do not match in the database.
        message = "LOGFA"; //login failed
    }
    return message;
}

QString ServerWindow::setRegisterResponse(QString receivedUsername, QString receivedPassword){
    //check if username exists
    QSqlQuery query(database);                                                                     //Create query
    query.prepare("SELECT * FROM Users WHERE username = :username");                               //prepares a SELECT command to select all rows from the Users table
    query.bindValue(":username", receivedUsername);                                                //bind pretended username
    query.exec();                                                                                  //execute query

    QString message;
    if (!query.next()) { //there isnt a row with matched username
        query.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");     //prepare a insert in users table command
        query.bindValue(":username", receivedUsername);                                            //bind pretended username
        query.bindValue(":password", receivedPassword);                                            //bind pretended password
        query.exec();                                                                              //rexecute created query
        qDebug() << "New account registered"; //The username doesnt exist and new account is registered
        message = "REGCO"; //register correct
    }
    else {
        qDebug() << "Username already exists" ; // The username already exists and no new acount is registered
        message = "REGFA"; //register failed
    }
    return message;
}

QString ServerWindow::setRoomResponse(Player* player, QString data){
    return QString("mudaristo");
}




