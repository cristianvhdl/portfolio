#include "gameserver.h"
#include <iostream>
using namespace sf;

GameServer::GameServer()
{
    port = 6006;
    database = new Connector();
}

void GameServer::awaitConnection()
{
    TcpListener listener;
    listener.listen(port);
    listener.accept(socket);
}

void GameServer::receiveRequestOrUpdateDatabase()
{
    char buffer[1024];
    size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    cout << "The client said: " << buffer << endl;
    if(string(buffer) == "getDatabase")
    {
        getEntireDatabase();
        return;
    }
    vector<string> info = split(buffer, ';');
    QString user, longestWordHit;
    int currentLevel, timePlayed, wordsHit, wordsMissed, longestStreak;

    for(size_t i=0; i<info.size(); i++)
    {
        string input = info[i];
        if (input.find("user") != string::npos)
            user = QString::fromStdString(info[i]).right(input.length() - 5);
        else if(input.find("longestWordHit") != string::npos)
            longestWordHit = QString::fromStdString(input).right(input.length() - 15);
        else if(input.find("level") != string::npos)
            stringstream(input) >> currentLevel;
        else if(info[i].find("timePlayed") != string::npos)
            stringstream(input) >> timePlayed;
        else if(info[i].find("wordsHit") != string::npos)
            stringstream(input) >> wordsHit;
        else if(info[i].find("wordsMissed") != string::npos)
            stringstream(input) >> wordsMissed;
        else if(info[i].find("longestStreak") != string::npos)
            stringstream(input) >> longestStreak;
    }
    // Send to database
    cout << "The client said: " << user.toStdString() << endl;
    database->updateStats(user, currentLevel, timePlayed, wordsHit, wordsMissed, longestWordHit, longestStreak);
    socket.disconnect();
}

void GameServer::updateClient(string message)
{
    socket.send(message.c_str(), message.size() + 1);
}

void GameServer::getEntireDatabase()
{
    //username, currentLevel, playedTime, wordsHit, wordsMissed, longestWordHit, longestStreak
//    string stats[] = {"username:", "currentLevel:", "playedTime:", "wordsHit:", "wordsMissed:", "longestWordHit:", "longestStreak:"};
    string toSend = "";
     vector<vector<QString> > entireDB = database->getEveryonesStats();
    for(int i=0; i<entireDB.size(); i++)
    {
        vector<QString> inside = entireDB[i];
        if(inside.size()!=0)
            toSend = toSend + "*";

        for(int j=0; j<inside.size(); j++)
        {
            toSend = toSend + inside[j].toStdString() + ";";
        }
    }
    updateClient(toSend);
    cout << "Sent:" << toSend << endl;
    socket.disconnect();
}

vector<string>& GameServer::split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> GameServer::split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
