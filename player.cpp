#include "player.h"

Player::Player(QString name)
{
    this->name = name;
    points = 0;
}

QString Player::getName(){
    return name;
}

long long Player::getSocketDescriptor(){
    return  socketDescriptor;
}

int Player::getPoints(){
    return points;
}

void Player::setPoints(int points){
    this->points = points;
}
