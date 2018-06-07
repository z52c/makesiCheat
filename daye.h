#ifndef DAYE_H
#define DAYE_H
#include <string.h>
#include <QString>
int getStringBetweenAandB(const char* a,const char* A,const char* B,char *find);

struct choiceResult
{
    QString title;
    QString answerA;
    QString answerB;
    QString answerC;
    QString answerD;
    QString answerE;
    QString answer;
};

struct tfResult
{
    QString title;
    QString answer;
};

#endif // DAYE_H
