#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question();
    void setText(QString text);
    void setAnswer(QString answer);
    void setPrice(int price);

    QString getText();
    QString getAnswer();
    int getPrice();

private:
    QString text;
    QString answer;
    int price;

};

#endif // QUESTION_H
