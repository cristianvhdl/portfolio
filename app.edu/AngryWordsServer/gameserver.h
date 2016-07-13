#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "SFML/Network.hpp"
#include "connector.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class GameServer
{
public:
    GameServer();
private:
    int m_score;
    int m_level;
//    Dictionary* m_dictionary;
    int port;
    sf::TcpSocket socket;
    Connector* database;

public:
    void awaitConnection();
    void receiveRequestOrUpdateDatabase();
    void getEntireDatabase();
    void updateClient(string);
    vector<string> split(const string&, char);
    vector<string> &split(const string&, char, vector<string>&);
};

#endif // GAMESERVER_H
