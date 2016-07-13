#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include "dictionary.h"
#include "SFML/Network.hpp"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = 0);
private:
    int m_score;
    int m_level;
    Dictionary* m_dictionary;
    sf::TcpSocket socket;

signals:
    //void updateScore(int score) const;
public slots:
    void newGame();
    void endGame();

    void newEnemy();
    void checkWord();

    //TODO: return a word instead of pointer
    //TODO: verify correctness on server side
    QString* getWord();
    void getDictionary(int difficulty);

    string receiveFromServer();
    void sendToServer(QString, QString, QString, QString, QString, QString, QString);
    vector<vector<string> > getEntireDatabase();
    vector<string> split(const string&, char);
    vector<string> &split(const string&, char, vector<string>&);
};

#endif // GAMESERVER_H
