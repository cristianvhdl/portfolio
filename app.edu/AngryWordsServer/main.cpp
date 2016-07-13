#include <QCoreApplication>
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer gameServer;
//    gameServer.awaitConnection();
    while (true)
    {
        gameServer.awaitConnection();
        gameServer.receiveRequestOrUpdateDatabase();
    }
    return a.exec();
}
