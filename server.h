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
#include "question.h"
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
    Question currentQuestion;
    Player *currentPlayer;
    QVector<Player> players;
    int ready;

signals:
    void showDialog(QString question);
    void showQuestion(QString player, QString question, QString answer);
    void addPlayer(QString player, int const &points);

public slots:
    void startServer();
    void incomingConnection(long long socketDescriptor);
    void sockReady();
    void sockDisc();

    void correctAnswer();
    void wrongAnswer();
    void nextQuestion();

private:

    void updatePoints();
    void blockButtons(bool block);
};

#endif // SERVER_H
