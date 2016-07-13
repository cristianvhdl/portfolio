#include "player.h"

Player::Player()
{

}

int Player ::getHighScore() const
{
    return highScore;
}

int Player::getLevel() const
{
    return level;
}

void Player::setHighScore(int hs)
{
    highScore = hs;
}

void Player::setLevel(int l)
{
    level = l;
}


