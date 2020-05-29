#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
public:
    Player(QString name);
    QString getName();
    void setName(QString name);
    int getPoints();
    void setPoints(int points);
    long long getSocketDescriptor();
    void setSocketDescriptor();
private:
    QString name;
    int points;
    long long socketDescriptor;
};

#endif // PLAYER_H
