#include "gameserver.h"
using namespace sf;

GameServer::GameServer(QObject *parent) : QObject(parent)
{
    m_score = 0;
    m_level = 1;
    m_dictionary = new Dictionary();
    socket.connect("127.0.0.1", 6006);
}

void GameServer::newGame()
{
    m_score = 0;
    m_level = 1;
    // start timers to spawn enemies
}

void GameServer::endGame()
{
    // destroy all the enemiers and stop all the timers
}

void GameServer::newEnemy()
{
    // spaw enemy
}

void GameServer::checkWord()
{

}

void GameServer::getDictionary(int difficulty)
{
    m_dictionary->getDictionary(difficulty);
}

QString *GameServer::getWord()
{
    return m_dictionary->getWord();
}

string GameServer::receiveFromServer()
{
    socket.connect("127.0.0.1", 6006);
    char buffer[4048];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "The server said: " << buffer << std::endl;
    socket.disconnect();
    return string(buffer);
}

void GameServer::sendToServer(QString username, QString currentLevel, QString playedTime, QString wordsHit, QString wordsMissed, QString longestWordHit, QString longestStreak)
{
    socket.connect("127.0.0.1", 6006);
    string message = "user:"+username.toStdString() + ";longestWordHit:"+longestWordHit.toStdString()
            + ";level:" + currentLevel.toStdString() + ";timePlayed:" + playedTime.toStdString()
            + ";wordsHit:" + wordsHit.toStdString() + ";wordsMissed:" + wordsMissed.toStdString()
            + ";longestStreak:" + longestStreak.toStdString() + ";";
    socket.send(message.c_str(), message.size()+1);
    socket.disconnect();
}

vector<vector<string> > GameServer::getEntireDatabase()
{
    socket.connect("127.0.0.1", 6006);
    string message = "getDatabase";
    socket.send(message.c_str(), message.size()+1);
    string db = receiveFromServer();
    cout << "Database:" << db << endl;
    vector<vector<string> > results;
    vector<string> students = split(db, '*');
    for(int i=0; i<students.size(); i++)
    {
        if(students[i] == "")
        {
            continue;
        }
        cout << "student: " << students[i] << endl;
        results.push_back(split(students[i], ';'));
    }
    socket.disconnect();
    return results;
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
