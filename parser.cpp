#include "parser.h"

Parser::Parser(QJsonDocument &doc)
{
    this->pDoc = &doc;
}

Parser::~Parser()
{

}

QJsonDocument Parser::getInit(){

    QJsonDocument doc = *pDoc;
    QString str = "";
    QJsonArray contents = doc.object().value("contents").toArray();

    QJsonObject obj;

    obj.insert("type", "initialization");

    for(int i = 1; i < 6; i++){

        obj.insert("price"+QString::number(i), doc.object().value("dif"+QString::number(i)).toInt());

    }

    for(int i = 0; i < 5; i++){

        obj.insert("heading"+QString::number(i+1), contents.at(i).toObject().value("heading"));

    }

    doc = QJsonDocument(obj);
    return doc;

}

QJsonObject Parser::getQuestion(int difficulty, int headingId){

    QJsonDocument doc = *pDoc;
    QJsonArray contents = doc.object().value("contents").toArray();
    QJsonArray questions = contents.at(headingId - 1).toObject().value("questions").toArray();
    QJsonObject question = questions.at(difficulty - 1).toObject();

    return question;

}
