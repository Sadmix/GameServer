#include "server.h"

Server::Server(){

    file = new QFile("E:\\Documents\\testGame.json");
    file->open(QIODevice::ReadOnly);
    gameDoc = QJsonDocument::fromJson(file->readAll());
    file->close();
    parser = new Parser(gameDoc);
    ready = 0;

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

                if(doc.object().value("operation") == "start"){
                Data = parser->getInit().toJson();
                socket->write(Data);
                socket->waitForBytesWritten(500);
                }

                if(doc.object().value("operation").toString() == "finish"){
                    ready++;
                }

                if(ready == 3){
                    Data = "{\"type\":\"game\", \"operation\":\"start\", \"name\":\"" + players[0].getName().toUtf8() + "\"}"; // сделать рандомного игрока
                    for(auto s : sockets){
                        s->waitForBytesWritten(1000);
                        s->write(Data);
                    }
                }


            } else if(doc.object().value("type").toString() == "regName"){

                QByteArray playerName = doc.object().value("name").toString().toUtf8();
                players.push_back(Player(playerName));
                QJsonArray names;
                for(auto p : players){
                    QJsonObject name;
                    name.insert("name", p.getName());
                    names.append(name);
                }
                QJsonObject obj;
                obj.insert("type", "updateNames");
                obj.insert("names", names);
                QJsonDocument doc(obj);
                Data = doc.toJson();
                for(auto s : sockets){
                        s->write(Data);
                }
                emit addPlayer(players.last().getName(), players.last().getPoints());

            }
            else if (doc.object().value("type").toString() == "chooseQuestion"){

                QJsonObject question = parser->getQuestion(doc.object().value("price").toString().toInt(), doc.object().value("headingId").toString().toInt());
                QByteArray questionText = question.value("text").toString().toUtf8();
                Data = "{\"type\":\"questionText\", \"value\" : \"" + questionText + "\"}";
                for(auto s : sockets){
                    s->write(Data);
                }

                currentQuestion.setText(question.value("text").toString());
                currentQuestion.setAnswer(question.value("answer").toString());
                currentQuestion.setPrice(question.value("price").toInt());

                showQuestion(currentPlayer->getName(), currentQuestion.getText(), currentQuestion.getAnswer());

            } else if (doc.object().value("type").toString() == "answer") {

                for(auto p : players){
                    if(p.getSocketDescriptor() == socket->socketDescriptor()){
                        currentPlayer = &p;
                        break;
                    }
                }

                blockButtons(true);

                emit showDialog(currentQuestion.getAnswer());
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

void Server::correctAnswer(){
    currentPlayer->setPoints(currentPlayer->getPoints() + currentQuestion.getPrice());
    updatePoints();
    blockButtons(false);
}

void Server::wrongAnswer(){
    currentPlayer->setPoints(currentPlayer->getPoints() + currentQuestion.getPrice());
    updatePoints();
    blockButtons(false);
}

void Server::nextQuestion(){
    Data = "{\"type\":\"game\", \"operation\":\"nextQuestion\"}";
    for(auto s : sockets){
        s->write(Data);
    }
}

void Server::updatePoints(){

    Data = "{\"type\":\"game\", \"operation\":\"updatePoints\", \"player\":\"" + currentPlayer->getName().toUtf8() + "\", \"points\":\"" + QString::number(currentPlayer->getPoints()).toUtf8() +"\"}";
    for(auto s : sockets){
        s->write(Data);
    }

}

void Server::blockButtons(bool block){
    QString operation;
    operation = block ? "blockButtons" : "unblockButtons";

    for(auto s : sockets){
        Data = "{\"type\":\"game\", \"operation\":\"" + operation.toUtf8() + "\"}";
        s->write(Data);
    }

}
