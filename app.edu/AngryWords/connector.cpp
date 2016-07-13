#include "connector.h"
#include <mysql/mysql.h>
#include <string>
#include <vector>

Connector::Connector()
{
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql,"atr.eng.utah.edu","cs3500_rileyj","IdleMind","cs3500_rileyj",0,0,0);
}

Connector::~Connector()
{
    mysql_close(connection);
}

bool Connector::isUser(QString username)
{
    //select exists(select 1 from User where username = 'user');

    std::string query = "select username from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    if(row != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Connector::login(QString username, QString password)
{
    std::string query = "select username, password from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    if(row == 0)
    {
        return false;
    }
    else if(password.toStdString() != row[1])
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Connector::getHighScore(QString username)
{
    //select currentLevel from User where username = 'user';

    std::string query = "select currentLevel from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return atoi(row[0]);

}

int Connector::totalPlayedTime(QString username)
{
    //select playedTime from User where username = 'user';

    std::string query = "select playedTime from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return atoi(row[0]);
}

int Connector::totalWordsHit(QString username)
{
    //select wordsHit from User where username = 'user';

    std::string query = "select wordsHit from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return atoi(row[0]);
}

int Connector::totalWordsMissed(QString username)
{
    //select wordsMissed from User where username = 'user';

    std::string query = "select wordsMissed from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return atoi(row[0]);
}

QString Connector::longestWordHit(QString username)
{
    //select longestWordHit from User where username = 'user';

    std::string query = "select longestWordHit from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return QString(row[0]);
}

int Connector::longestWordStreak(QString username)
{
    //select longestStreak from User where username = 'user';

    std::string query = "select longestStreak from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    return atoi(row[0]);
}

bool Connector::isTeacher(QString username)
{
    //select isTeacher from User where username = 'user';

    std::string query = "select isTeacher from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    if(row[0] != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Connector::addUser(QString username, QString password, bool isTeacher)
{
    //insert into User (`username`, 'isTeacher') VALUES ('user3', '0');
    //INSERT INTO `cs3500_rileyj`.`User` (`username`, `isTeacher`) VALUES ('user4', 1);
    //insert into User (`username`, `password`, `isTeacher`) VALUES ('user9', 'test', 1);


    std::string teacher = "";

    if(isTeacher)
    {
        teacher = "1";
    }
    else
    {
        teacher = "0";
    }

    std::string query = "insert into User (`username`, `password`, `isTeacher`) VALUES ('" + username.toStdString() + "', '" + password.toStdString() + "', " + teacher + ");";

    mysql_query(connection, query.c_str());

}

void Connector::addStudent(QString teacher, QString student)
{
    //insert into Teaches (`teacher`, `student`) VALUES ('user', 'user1');

    std::string query = "insert into Teaches (`teacher`, `student`) VALUES ('" + teacher.toStdString() + "', '" + student.toStdString() + "');";
    mysql_query(connection, query.c_str());

}

std::vector<std::vector<QString> > Connector::getEveryonesStats()
{
    std::string query = "select username, currentLevel, playedTime, wordsHit, wordsMissed, longestWordHit, longestStreak, isTeacher from User order by currentLevel desc;";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;

   std::vector<std::vector<QString> > vRows(mysql_num_rows(result));


    int j = 0;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        std::vector<QString> vColumns(mysql_num_fields(result));

        for(size_t i = 0; i < mysql_num_fields(result); i++)
        {
            vColumns[i] = row[i];
        }

        vRows[j] = vColumns;
        j++;
    }

    return vRows;

}

std::vector<std::vector<QString> > Connector::getTeachersStudentsStats(QString teacher)
{
    std::string query = "SELECT username, currentLevel, playedTime, wordsHit, wordsMissed, longestWordHit, longestStreak, isTeacher FROM User, Teaches where student = username and teacher = '" + teacher.toStdString() + "' order by currentLevel desc;";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;

   std::vector<std::vector<QString> > vRows(mysql_num_rows(result));


   int j = 0;
   while((row = mysql_fetch_row(result)) != NULL)
   {
       std::vector<QString> vColumns(mysql_num_fields(result));

       for(size_t i = 0; i < mysql_num_fields(result); i++)
       {
           vColumns[i] = row[i];
       }

       vRows[j] = vColumns;
       j++;
   }

   return vRows;

}


std::vector<QString> Connector::getStudentStats(QString username)
{
    std::string query = "select username, currentLevel, playedTime, wordsHit, wordsMissed, longestWordHit, longestStreak from User where username = '" + username.toStdString() + "';";
    mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);


    std::vector<QString> stats;

    for(size_t i = 0; i < mysql_num_fields(result); i++)
    {
        stats.push_back(row[i]);
    }

    return stats;
}

void Connector::updateStats(QString user, int score, int timePlayed, int wordsHit, int wordsMissed, QString longestWordHit, int longestStreak)
{
    //Should the checks happen here or in the server?

    std::vector<QString> stats = getStudentStats(user);

    std::string hScore = QString::number(stats[1].toInt()).toStdString();

    std::string tPlayed = QString::number(timePlayed + stats[2].toInt()).toStdString();

    std::string wHit = QString::number(wordsHit + stats[3].toInt()).toStdString();

    std::string wMissed = QString::number(wordsMissed + stats[4].toInt()).toStdString();

    std::string lWord = QString(stats[5]).toStdString();

    if(score > stats[1].toInt())
    {
        hScore = QString::number(score).toStdString();
    }

    if(longestWordHit.size() > stats[5].size())
    {
        lWord = longestWordHit.toStdString();
    }

    std::string lStreak = QString::number(stats[6].toInt()).toStdString();

    if(longestStreak > stats[6].toInt())
    {
        lStreak = QString::number(longestStreak).toStdString();
    }


    //update User set `currentLevel`='1', `playedTime`='1', `wordsHit`='1', `wordsMissed`='1', `longestWordHit`='thing', `longestStreak`='2' where `username`='user';

    std::string query = "update User set `currentLevel`='" + hScore + "', `playedTime`='" + tPlayed + "', `wordsHit`='" + wHit + "', `wordsMissed`='" + wMissed + "', `longestWordHit`='" + lWord + "', `longestStreak`='" + lStreak + "' where `username`='" + user.toStdString() + "';";
    mysql_query(connection, query.c_str());
}
