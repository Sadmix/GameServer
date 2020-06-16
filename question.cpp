#include "question.h"

Question::Question()
{

}

void Question::setText(QString text){
    this->text = text;
}

void Question::setAnswer(QString answer){
    this->answer = answer;
}
void Question::setPrice(int price){
    this->price = price;
}

QString Question::getText(){
    return text;
}

QString Question::getAnswer(){
    return answer;
}

int Question::getPrice(){
    return price;
}
