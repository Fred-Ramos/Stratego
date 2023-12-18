#include "ServerWindow.h"
#include "tcpserver.h"
#include "player.h"
#include "Button.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

#include <QRandomGenerator>

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
    query.exec("CREATE TABLE IF NOT EXISTS GameRooms (roomName TEXT, password TEXT)");

    //delete usernames and passwords if needed:
    query.exec("DELETE FROM Users");

    //when server starts, delete all previous rooms
    query.exec("DELETE FROM GameRooms");



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

    QString identifier = data.left(5);
    //determine response to the client
    if (identifier == QString("REGIS")){ //Register message
        //read pretended username and password
        int changeIndex = data.indexOf("|");
        QString thisUsername = data.mid(5, changeIndex - 5); //from position 5, read "changeIndex - 5" characters
        QString thisPassword = data.mid(changeIndex + 1, data.size() - 1 - changeIndex);
        qDebug() << thisUsername;
        qDebug() << thisPassword;
        ResponseMessage = setRegisterResponse(thisUsername, thisPassword);
        gameServer->writeToClient(socket, ResponseMessage);
    }
    else if (identifier == QString("LOGIN")){ //Login message
        //read pretended username and password
        int changeIndex = data.indexOf("|");
        QString thisUsername = data.mid(5, changeIndex - 5); //from position 5, read "changeIndex - 5" characters
        QString thisPassword = data.mid(changeIndex + 1, data.size() - 1 - changeIndex);
        qDebug() << thisUsername;
        qDebug() << thisPassword;
        ResponseMessage = setLoginResponse(thisUsername, thisPassword); //run new login function

        if (ResponseMessage == QString("LOGCO")){ //if login was completed, add account to players
            qDebug() << "response being sent, new player being added";
            Player* newplayer;
            newplayer = new Player(thisUsername, connectionIP, connectionSourcePort);
            Players.append(newplayer);
            qDebug() << "New Player gameboard: ";
            newplayer->PrintBoard(false); //not inverted board
            qDebug() << "Number of Player: " << Players.size();
        }
        gameServer->writeToClient(socket, ResponseMessage);
    }
    else if (identifier == QString("SETRO")){ //set room message
        qDebug() << "Room message received";
        int endIndex = data.indexOf("|");
        qDebug() << endIndex;
        QString room = data.mid(5, endIndex - 5); //from position 5, read "changeIndex - 5" characters
        qDebug() << "whole data: " << data;
        qDebug() << "New Room: " << room;
        for (Player* player : Players) {
            qDebug() << "1st Running through player's IPs: " << player->getIP();
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game room
                ResponseMessage = setRoomResponse(player, room);
            }
        }
        gameServer->writeToClient(socket, ResponseMessage);
    }
    else if (identifier == QString("JOIRO")){ //join room message
        qDebug() << "Join Room message received";
        int endIndex = data.indexOf("|");
        qDebug() << endIndex;
        QString room = data.mid(5, endIndex - 5); //from position 5, read "changeIndex - 5" characters
        qDebug() << "whole data: " << data;
        qDebug() << "New Room: " << room;
        Player* thisPlayer = nullptr;
        for (Player* player : Players) {
            qDebug() << "2nd Running through player's IPs/Ports: " << player->getIP() << player->getSourcePort();
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game room
                thisPlayer = player;
                setJoinRoomResponse(thisPlayer, socket, connectionIP, connectionSourcePort, room);
            }
        }
    }
    else if(identifier == QString("SETUP")){ //setting up pieces
        qDebug() << "Setup pieces message received";
        int dataLength = data.size();
        QString positions = data.mid(5, dataLength - 5);
        qDebug() << "positions data: " << positions;
        Player* thisPlayer = nullptr;
        for (Player* player : Players) {
            qDebug() << "3rd Running through player's IPs/Ports: " << player->getIP() << player->getSourcePort();
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game board
                thisPlayer = player;
                setPiecesResponse(thisPlayer, socket, connectionIP, connectionSourcePort, positions);
            }
        }
    }
    else if (identifier == QString("MOVEP")){ //piece move
        int dataLength = data.size();
        QString move = data.mid(5, dataLength - 5);
        qDebug() << "move data: " << move;
        Player* thisPlayer = nullptr;
        for (Player* player : Players) {
            qDebug() << "4th Running through player's IPs/Ports: " << player->getIP() << player->getSourcePort();
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game board
                thisPlayer = player;
                setMoveResponse(thisPlayer, socket, connectionIP, connectionSourcePort, move);
            }
        }
    }
    else if (identifier == QString("LEAVE")){
        Player* thisPlayer = nullptr;
        for (Player* player : Players) {
            qDebug() << "4th Running through player's IPs/Ports: " << player->getIP() << player->getSourcePort();
            if (player->getIP() == connectionIP && player->getSourcePort() == connectionSourcePort ) {
                // Found player with the given IP and source, set its game board
                thisPlayer = player;
                leaveOtherGame(thisPlayer, socket, connectionIP, connectionSourcePort);
                thisPlayer->cleanGameData();
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

QString ServerWindow::setRoomResponse(Player* player, QString thisRoom){
    //check if room exists
    QSqlQuery query(database);                                                                     //Create query
    query.prepare("SELECT * FROM GameRooms WHERE roomName = :roomName");                           //prepares a SELECT command to select all rows from the Users table
    query.bindValue(":roomName", thisRoom);                                                        //bind pretended room
    query.exec();                                                                                  //execute query

    QString message;
    if (!query.next()) { //there isnt a row with matched room
        query.prepare("INSERT INTO GameRooms (roomName) VALUES (:roomName)");                      //prepare a insert in users table command
        query.bindValue(":roomName", thisRoom);                                                    //bind pretended room
        query.exec();                                                                              //rexecute created query
        qDebug() << "New room registered: " << thisRoom ;                                                         //The room doesnt exist and new room is registered
        player->setRoom(thisRoom); //atribute room to player
        message = "ROCSU"; //Room registered
    }
    else {
        qDebug() << "Room already exists" ; // The username already exists and no new acount is registered
        message = "ROCFA"; //Room already exists
    }
    return message;
}

void ServerWindow::setJoinRoomResponse(Player* thisPlayer, QTcpSocket* thisSocket, QString thisIp, QString thisSourcePort, QString thisRoom){
    //check if room exists
    QSqlQuery query(database);                                                                     //Create query
    query.prepare("SELECT * FROM GameRooms WHERE roomName = :roomName");                           //prepares a SELECT command to select all rows from the Users table
    query.bindValue(":roomName", thisRoom);                                                        //bind pretended room
    query.exec();                                                                                  //execute query

    QString message;
    if (!query.next()) { //there isnt a row with matched room
        qDebug() << "Couldnt join " << thisRoom;                                                  //The room doesnt exist
        message = "JOIFA"; //Join failed
        gameServer->writeToClient(thisSocket, message);
    }
    else {
        qDebug() << "Joined room" << thisRoom ; // The room exists
        thisPlayer->setRoom(thisRoom); //atribute room to this player
       //find ip and port of the other player with the same room and respective socket:
        Player* otherPlayer = nullptr;
        QString otherIP;
        QString otherSourcePort;
        QString otherRoom;
        QTcpSocket* otherSocket;
        //send start as red/start as blue message to both clients
        for (Player* player : Players) {
            otherIP = player->getIP();
            otherSourcePort = player->getSourcePort();
            otherRoom = player->getRoom();
            if ( (otherIP != thisIp || otherSourcePort != thisSourcePort) && player->getRoom() == thisRoom ) { //if sources are not the same, and they share the same room, start the game for both players, each with a diferent color
                qDebug() << "found other player " << player->getIP() << player->getSourcePort();
                otherPlayer = player;

                // Found player with the given IP and source, get his socket
                otherSocket = gameServer->findConnection(otherIP, otherSourcePort);
                qDebug() << "socket" << otherSocket;

                qDebug() << "other guy IPs" << otherSocket->peerAddress().toString();
                qDebug() << "other guy SourcePort" << QString::number(otherSocket->peerPort());;

                QString thisName = thisPlayer->getName();
                qDebug() << "This Player's name: " << thisName;
                QString otherName = otherPlayer->getName();
                qDebug() << "Other Player's name: " << otherName;


                QString thisMessage;
                QString otherMessage;


                if (otherSocket != nullptr){ //if not null
                    double random = QRandomGenerator::global()->generateDouble(); //generate random number
                    if (random < 0.5){
                        thisMessage = QString("SETRE") + otherName;
                        otherMessage = QString("SETBL") + thisName;
                        thisPlayer->setColor(QString("REDPLAYER"));
                        otherPlayer->setColor(QString("BLUEPLAYER"));
                        gameServer->writeToClient(thisSocket, thisMessage); //Join as red, and other player's name
                        gameServer->writeToClient(otherSocket, otherMessage); //Join as blue, and other player's name
                    }
                    else{
                        thisMessage = QString("SETBL") + otherName;
                        otherMessage = QString("SETRE") + thisName;
                        thisPlayer->setColor(QString("BLUEPLAYER"));
                        otherPlayer->setColor(QString("REDPLAYER"));
                        gameServer->writeToClient(thisSocket, thisMessage); //Join as red, and other player's name
                        gameServer->writeToClient(otherSocket, otherMessage); //Join as blue, and other player's name
                    }
                }
                else{
                    qDebug() << "Error, no socket found";
                }
            }
        }
    }
}

void ServerWindow::setPiecesResponse(Player *thisPlayer, QTcpSocket *thisSocket, QString thisIp, QString thisSourcePort, QString PositionData){
    if (thisPlayer->getSetUpData() == QString("")){
        thisPlayer->setSetUpData(PositionData);
    }
    QString thisSetUpData = PositionData;
    QString thisRoom = thisPlayer->getRoom(); //room of this player
    QString thisColor = thisPlayer->getColor(); //color of this player
    //find ip and port of the other player with the same room and diferent color
    Player* otherPlayer = nullptr;
    QString otherIP;
    QString otherSourcePort;
    QString otherColor;
    QString otherSetUpData;
    QTcpSocket* otherSocket;
    for (Player* player : Players) {
        otherIP = player->getIP();
        otherSourcePort = player->getSourcePort();
        otherColor = player->getColor();
        if ( player->getRoom() == thisRoom && player->getColor() != thisColor ) { //if they share the same room and have diferent colors
            qDebug() << "setup found other player " << player->getIP() << player->getSourcePort();
            otherPlayer = player;
            if (otherPlayer->getSetUpData() != QString("")){ //if other player has no setup data, SETUP the initial board for both players, and send message back confirming game starting
                otherSetUpData = otherPlayer->getSetUpData();
                QString thisC; //this color identifier
                QString otherC; //other color identifier
                if (thisPlayer->getColor() == QString("REDPLAYER")){//if this player is red:
                    thisC = QString("R");
                    otherC = QString("B");
                }
                else{
                    thisC = QString("B");
                    otherC = QString("R");
                }
                //First place this pieces in this's board
                for (int k = 0; k < 40; k++){ //every 4 characters
                    thisPlayer->gameBoard[thisSetUpData.at(4*k + 0).digitValue()][thisSetUpData.at(4*k + 1).digitValue()] = thisC + thisSetUpData.at(4*k + 2) + thisSetUpData.at(4*k + 3); //last 2 characters of each 4 characters
                }
                //Then place other pieces in other's board
                for (int k = 0; k < 40; k++){ //every 4 characters
                    otherPlayer->gameBoard[otherSetUpData.at(4*k + 0).digitValue()][otherSetUpData.at(4*k + 1).digitValue()] = otherC + otherSetUpData.at(4*k + 2) + otherSetUpData.at(4*k + 3);
                }
                //Then complete each player's board with the other's inverted half board:
                QVector<QVector<QString>> invertedThisPlayerBoard = thisPlayer->invertBoard();
                // Copy the first 4 lines from inverted redBoard to blueBoard
                for(int i = 0; i < 4; ++i) {
                    for(int j = 0; j < 10; j++){
                        otherPlayer->gameBoard[i][j] = invertedThisPlayerBoard[i][j];
                    }
                }
                QVector<QVector<QString>> invertedOtherPlayerBoard = otherPlayer->invertBoard();
                // Copy the first 4 lines from inverted blueBoard to redBoard
                for(int i = 0; i < 4; ++i) {
                    for(int j = 0; j < 10; j++){
                        thisPlayer->gameBoard[i][j] = invertedOtherPlayerBoard[i][j];
                    }
                }
                qDebug() << "Boards after setup:";
                qDebug() << "This Board:";
                thisPlayer->PrintBoard(false);
                qDebug() << "Other Board:";
                otherPlayer->PrintBoard(false);

                //Initial boards organized for both players, now send message to both clients to start game
                // get other player's socket
                otherSocket = gameServer->findConnection(otherIP, otherSourcePort);
                //send start game message
                QString message = QString("START");
                gameServer->writeToClient(thisSocket, message);
                gameServer->writeToClient(otherSocket, message);
            }
        }
    }
}

void ServerWindow::setMoveResponse(Player *thisPlayer, QTcpSocket *thisSocket, QString thisIp, QString thisSourcePort, QString thisMove){
    int SrcRow = thisMove.at(0).digitValue();
    int SrcCol = thisMove.at(1).digitValue();
    int DestRow = thisMove.at(2).digitValue();
    int DestCol = thisMove.at(3).digitValue();
    qDebug() << "confirm data: ";
    qDebug() << SrcRow << "|" << SrcCol << "|" << DestRow << "|" << DestCol;

    QString thisRoom = thisPlayer->getRoom(); //room of this player
    QString thisColor = thisPlayer->getColor(); //color of this player
    //find ip and port of the other player with the same room and diferent color
    Player* otherPlayer = nullptr;
    QString otherIP;
    QString otherSourcePort;
    QString otherColor;
    QTcpSocket* otherSocket;
    for (Player* player : Players) {
        otherIP = player->getIP();
        otherSourcePort = player->getSourcePort();
        otherColor = player->getColor();
        if ( player->getRoom() == thisRoom && player->getColor() != thisColor ) { //if they share the same room and have diferent colors, found other player!
            qDebug() << "move found other player " << player->getIP() << player->getSourcePort();
            otherPlayer = player;

            //do move for both boards and both players

            QString thisRank = thisPlayer->gameBoard[SrcRow][SrcCol].right(2);
            QString otherRank = thisPlayer->gameBoard[DestRow][DestCol].right(2);
            qDebug() << thisRank << "is atacking " << otherRank;
            int atackResult = ComparePiece(thisRank, otherRank);

            QString thisMessage = QString("MOVAR"); //MOVE ATACK RESPONSE
            QString otherMessage = QString("MOVDR"); //MOVE DEFENSE RESPONSE



            if (atackResult == 1){ //if atacking piece wins
                QString atackingPiece = thisPlayer->gameBoard[SrcRow][SrcCol];
                thisPlayer->gameBoard[DestRow][DestCol] = atackingPiece;
                thisPlayer->gameBoard[SrcRow][SrcCol] = "0N";

                otherPlayer->gameBoard[9 - DestRow][9 - DestCol] = atackingPiece;
                otherPlayer->gameBoard[9 - SrcRow][9 - SrcCol] = "0N";

                thisMessage.append("W"); //atacker wins
                otherMessage.append("L"); //defender looses

                thisMessage.append(otherRank); //atacking player now knows rank of defending piece
                otherMessage.append(QString::number(9 - SrcRow) + QString::number(9 - SrcCol) + QString::number(9 - DestRow) + QString::number(9 - DestCol)); //defending player knows what piece moved and to where
                otherMessage.append(thisRank); //defending piece knows atacking piece rank;
            }
            else if(atackResult == 0 ){ //if both pieces loose
                thisPlayer->gameBoard[DestRow][DestCol] = "0N";
                thisPlayer->gameBoard[SrcRow][SrcCol] = "0N";

                otherPlayer->gameBoard[9 - DestRow][9 - DestCol] = "0N";
                otherPlayer->gameBoard[9 - SrcRow][9 - SrcCol] = "0N";

                thisMessage.append("D"); //draw
                otherMessage.append("D"); //draw

                thisMessage.append(otherRank); //atacking player knows destination square and now knows rank of defending piece
                otherMessage.append(QString::number(9 - SrcRow) + QString::number(9 - SrcCol) + QString::number(9 - DestRow) + QString::number(9 - DestCol)); //defending player knows what piece moved and to where
                otherMessage.append(thisRank); //defending piece knows atacking piece rank;
            }
            else if(atackResult == -1 ){ //if atacking piece looses
                thisPlayer->gameBoard[SrcRow][SrcCol] = "0N"; //only atacking source square is cleaned, end square stays with defending piece, that survived

                otherPlayer->gameBoard[9 - SrcRow][9 - SrcCol] = "0N";

                thisMessage.append("L"); //atacker looses
                otherMessage.append("W"); //defender wins

                thisMessage.append(otherRank); //atacking player now knows rank of defending piece
                otherMessage.append(QString::number(9 - SrcRow) + QString::number(9 - SrcCol) + QString::number(9 - DestRow) + QString::number(9 - DestCol)); //defending player knows what piece moved and to where
                otherMessage.append(thisRank); //defending piece knows atacking piece rank;
            }
            //ATACKING FLAG CONDITION MISSING!!!!!!!!!!!!!!!!!!!!!!!
            else if (atackResult == 2){ //if atacked a flag
                QString atackingPiece = thisPlayer->gameBoard[SrcRow][SrcCol];
                thisPlayer->gameBoard[DestRow][DestCol] = atackingPiece;
                thisPlayer->gameBoard[SrcRow][SrcCol] = "0N";

                otherPlayer->gameBoard[9 - DestRow][9 - DestCol] = atackingPiece;
                otherPlayer->gameBoard[9 - SrcRow][9 - SrcCol] = "0N";

                thisMessage.append("G"); //atacker wins
                otherMessage.append("G"); //defender looses

                thisMessage.append(otherRank); //atacking player now knows rank of defending piece
                otherMessage.append(QString::number(9 - SrcRow) + QString::number(9 - SrcCol) + QString::number(9 - DestRow) + QString::number(9 - DestCol)); //defending player knows what piece moved and to where
                otherMessage.append(thisRank); //defending piece knows atacking piece rank;
            }
            qDebug() << "Boards after move:";
            qDebug() << "This Board:";
            thisPlayer->PrintBoard(false);
            qDebug() << "Other Board:";
            otherPlayer->PrintBoard(false);
            // get other player's socket
            otherSocket = gameServer->findConnection(otherIP, otherSourcePort);
            //server boards have been updated, now send message to clients about the move result
            gameServer->writeToClient(thisSocket, thisMessage);
            gameServer->writeToClient(otherSocket, otherMessage);
        }
    }
}


//Compare function, returns: 0(both pieces die), 1(atacking piece wins), -1(defending piece wins)
int ServerWindow::ComparePiece(QString thisRank, QString otherRank) {                      // check if rank of piece is higher
    qDebug() << "Comparing atacking: " << thisRank << "with defendind: " << otherRank;
    bool numeric;
    int O = otherRank.toInt(&numeric);       //other rank, numeric
    if (otherRank == "0N"){                  //if empty
        return 1;
    }
    else if (numeric){ //if is a ranked piece(is a number)
        int T = thisRank.toInt();

        if ((T == 1) && (O == 10)){ //if spy is atacking and marshal defending, spy wins(only exception to rank rule)
            return 1; //nothing changes, defending piece is deleted
        }
        else if (T > O){
            return 1; //ATACKING PIECE WINS
        }
        else if (O > T){
            return -1; //DEFENDING PIECE WINS
        }
        else if(T == O){
            return 0; //BOTH PIECES LOOSE
        }
    }
    else if (otherRank == "0B"){
        if (thisRank == "03"){
            return 1; //Miner disarms bomb, bomb piece looses
        }
        else{
            return -1; //Bomb "explodes, wins" and atacking piece looses (Bomb stays in place)
        }
    }
    else if (otherRank == "0F"){ //defending piece is a flag
        return 2; //atacking player wins
    }
    return 1;
}

void ServerWindow::leaveOtherGame(Player *thisPlayer, QTcpSocket *thisSocket, QString thisIp, QString thisSourcePort){
    QString thisRoom = thisPlayer->getRoom(); //room of this player

    //check if room exists and delete it from SQL table
    QSqlQuery query(database);                                                                     //Create query
    query.prepare("SELECT * FROM GameRooms WHERE roomName = :roomName");                           //prepares a SELECT command to select all rows from the Users table
    query.bindValue(":roomName", thisRoom);                                                        //bind pretended room
    query.exec();                                                                                  //execute query

    if (!query.next()) { //there isnt a row with matched room
        qDebug() << "Room doesnt exist, no need to delete it" ;
    }
    else {
        qDebug() << "Room exists, deleting it" ; // The username already exists and no new acount is registered

        // Delete the room
        QSqlQuery deleteQuery(database);
        deleteQuery.prepare("DELETE FROM GameRooms WHERE roomName = :roomName");
        deleteQuery.bindValue(":roomName", thisRoom);
        deleteQuery.exec();
    }


    QString thisColor = thisPlayer->getColor(); //color of this player
    //find ip and port of the other player with the same room and diferent color
    Player* otherPlayer = nullptr;
    QString otherIP;
    QString otherSourcePort;
    QString otherColor;
    QTcpSocket* otherSocket;
    for (Player* player : Players) {
        otherIP = player->getIP();
        otherSourcePort = player->getSourcePort();
        otherColor = player->getColor();
        if ( player->getRoom() == thisRoom && player->getColor() != thisColor ) { //if they share the same room and have diferent colors, found other player!
            qDebug() << "move found other player " << player->getIP() << player->getSourcePort();
            otherPlayer = player;
            // get other player's socket
            otherSocket = gameServer->findConnection(otherIP, otherSourcePort);
            //send message to other player, that this player left the game
            gameServer->writeToClient(otherSocket, QString("PLEFT")); //PLAYER LEFT
            //clean other player's game data
            otherPlayer->cleanGameData();
        }
    }
}




