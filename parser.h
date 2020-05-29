#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QString>
#include <QList>
#include <QDebug>

class Parser
{
public:
    Parser(QJsonDocument &pDoc);
    ~Parser();

    QJsonDocument *pDoc;
    QFile *file;


    QJsonDocument getInit();
    QJsonObject getQuestion(int difficulty, int headingId);
};

#endif // PARSER_H
