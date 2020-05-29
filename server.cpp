#include "server.h"

Server::Server(){

    file = new QFile("E:\\Documents\\testGame.json");
    file->open(QIODevice::ReadOnly);
    gameDoc = QJsonDocument::fromJson(file->readAll());
    file->close();
    parser = new Parser(gameDoc);

}

Server::~Server(){

}

void Server::startServer(){

    if(this->listen(QHostAddress::Any, 5555)){
        qDebug() << "Listening";
    }else {
        qDebug() << "Not listening";
    }

}

void Server::incomingConnection(long long socketDescriptor){

    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

        connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));

    qDebug() << socketDescriptor << "Client connected";
    socket->write("{ \"type\" : \"connection\", \"status\" : \"true\"}");
    sockets.push_back(socket);
}

void Server::sockReady(){
    for(auto socket : sockets){

        Data = socket->readAll();
        doc = QJsonDocument::fromJson(Data, &docErr);

        if(docErr.errorString().toInt() == QJsonParseError::NoError){

            if(doc.object().value("type") == "initialization"){

                Data = parser->getInit().toJson();
                socket->write(Data);
                socket->waitForBytesWritten(500);

            } else if(doc.object().value("type").toString() == "regName"){

                QByteArray playerName = doc.object().value("name").toString().toUtf8();
                players.push_back(Player(playerName));
                Data = "{\"type\":\"updateName\",\"name\":\"" + playerName + "\"}";
                for(auto socket : sockets){
                    socket->write(Data);
                }

                if(sockets.count() == 3){

                    // init start game

                }

            } else if(doc.object().value("type").toString() == "chooseQuestion"){

                // QJsonObject question = parser->getQuestion(doc.object().value("difficulty").toInt());
                QByteArray questionText;
                Data = "{\"type\":\"questionText\", \"value\" : \"" + questionText + "\"}";
                socket->write(Data);
                // show question and answer

            } else if(doc.object().value("type").toString() == "answer") {

                // correct ot not?
                // signal to open dialog

            }
        }
    }
}

void Server::sockDisc(){

    for(auto socket : sockets){
        if(socket->state() == QAbstractSocket::SocketState::UnconnectedState){
            qDebug() << "Disconnected";
            sockets.removeAt(sockets.indexOf(socket));
            socket->deleteLater();
        }
    }
}
