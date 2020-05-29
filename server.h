#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

#include "parser.h"
#include "player.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();

    QList<QTcpSocket *> sockets;
    QByteArray Data;
    QJsonDocument doc;
    QJsonDocument gameDoc;
    QJsonParseError docErr;
    QFile *file;
    Parser *parser;
    QString currentAnswer;
    QVector<Player> players;

public slots:
    void startServer();
    void incomingConnection(long long socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // SERVER_H
