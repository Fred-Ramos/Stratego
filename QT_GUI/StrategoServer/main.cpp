#include "ServerWindow.h"
#include "tcpserver.h"

#include <QApplication>

ServerWindow* serverwindow; //global variable
TCPServer* gameServer;      //global variable

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    serverwindow = new ServerWindow();

    gameServer = new TCPServer();

    serverwindow->show();
    serverwindow->displayVariables(); //start the game
    return a.exec();
}
