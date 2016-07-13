#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <QString>
#include <mysql/mysql.h>
#include <vector>
#include <string>


class Connector
{
    QString user;
    MYSQL *connection, mysql;

public:
    Connector();
    ~Connector();
    bool login(QString username, QString password);
    bool isUser(QString username);
    int currentLevel(QString username);
    int totalPlayedTime(QString username);
    int totalWordsHit(QString username);
    int totalWordsMissed(QString username);
    QString longestWordHit(QString username);
    int longestWordStreak(QString username);
    bool isTeacher(QString username);
    void addUser(QString username, QString password, bool isTeacher);
    void addStudent(QString teacher, QString student);
    std::vector<std::vector<QString> > getEveryonesStats();
    std::vector<std::vector<QString> > getTeachersStudentsStats(QString teacher);
    std::vector<QString> getStudentStats(QString username);
    void updateStats(QString user, int currentLevel, int timePlayed, int wordsHit, int wordsMissed, QString longestWordHit, int longestStreak);
};

#endif // CONNECTOR_H
