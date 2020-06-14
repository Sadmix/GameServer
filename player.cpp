#include "player.h"

Player::Player(QString name)
{
    this->name = name;
    points = 0;
}

QString Player::getName(){
    return name;
}
