#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
public:
    Player();

    //stores player's name
    QString name;

    int health;

    //getters and setters for the player's high score (highest WPM) and highest level reached
    int getHighScore() const;
    int getLevel() const;

    void setHighScore(int hs);
    void setLevel(int l);

private:
    //highest level the player has obtained
    int level;

    //best WPM the player has reached
    int highScore;
};

#endif // PLAYER_H
