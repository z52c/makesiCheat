#include "db4makesi.h"
#include <QtDebug>

db4Makesi::db4Makesi(QObject *parent) : QObject(parent)
{
    db=new QSqlDatabase();
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        *db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        *db = QSqlDatabase::addDatabase("QSQLITE");
        db->setDatabaseName("daye.db");
        //db->setUserName("daye");
        //db->setPassword("dayenihao");
    }
    if (!db->open())
    {
        qDebug() << "Error: Failed to connect database." << db->lastError();
    }
    else
    {
       // _create_tables();
    }
}

void db4Makesi::_create_tables()
{
    QSqlQuery sql_query;
    QString create_sql = "create table singleChoice (id INTEGER PRIMARY KEY AUTOINCREMENT, title varchar(255), answerA varchar(255),answerB varchar(255),answerC varchar(255),answerD varchar(255),answer varchar(10))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table singleChoice created!";
    }
    create_sql = "create table multipleChoice (id INTEGER PRIMARY KEY AUTOINCREMENT, title varchar(255), answerA varchar(255),answerB varchar(255),answerC varchar(255),answerD varchar(255),answerE varchar(255),answer varchar(10))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table multipleChoice created!";
    }
    create_sql = "create table tf (id INTEGER PRIMARY KEY AUTOINCREMENT, title varchar(255),answer varchar(20))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table tf created!";
    }
}

bool db4Makesi::insertSingleChoice(QString inTitle, QString inAnswerA, QString inAnswerB, QString inAnswerC, QString inAnswerD, QString inAnswer)
{
    QSqlQuery sql_query;
    QString insert_sql=QString("INSERT INTO singleChoice VALUES(NULL,\'%1\',\'%2\',\'%3\',\'%4\',\'%5\',\'%6\')").arg(inTitle).arg(inAnswerA).arg(inAnswerB).arg(inAnswerC).arg(inAnswerD).arg(inAnswer);
    if(!sql_query.exec(insert_sql))
    {
        qDebug()<<insert_sql;
        qDebug() << sql_query.lastError();
        return false;
    }
    else{
        return true;
    }
}

bool db4Makesi::insertMultipleChoice(QString inTitle, QString inAnswerA, QString inAnswerB, QString inAnswerC, QString inAnswerD, QString inAnswerE, QString inAnswer)
{
    QSqlQuery sql_query;
    QString insert_sql=QString("INSERT INTO multipleChoice VALUES(NULL,\'%1\',\'%2\',\'%3\',\'%4\',\'%5\',\'%6\',\'%7\')").arg(inTitle).arg(inAnswerA).arg(inAnswerB).arg(inAnswerC).arg(inAnswerD).arg(inAnswerE).arg(inAnswer);
    if(!sql_query.exec(insert_sql))
    {
        qDebug()<<insert_sql;
        qDebug() << sql_query.lastError();
        return false;
    }
    else{
        return true;
    }
}

bool db4Makesi::insertTF(QString inTitle, QString inAnswer)
{
    QSqlQuery sql_query;
    QString insert_sql=QString("INSERT INTO tf VALUES(NULL,\'%1\',\'%2\')").arg(inTitle).arg(inAnswer);
    if(!sql_query.exec(insert_sql))
    {
        qDebug()<<insert_sql;
        qDebug() << sql_query.lastError();
        return false;
    }
    else{
        return true;
    }
}


bool db4Makesi::isExistInSingleChoice(QString inTitle)
{
    QSqlQuery sql_query;
    QString select_sql = QString("SELECT * FROM singleChoice WHERE title = \'%1\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        int i=0;
        while(sql_query.next())
        {
           i++;
        }
        if(i)
        {
            return true;
        }else
        {
            return false;
        }
    }
}

bool db4Makesi::isExistInMultipleChoice(QString inTitle)
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from multipleChoice where title = \'%1\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        int i=0;
        while(sql_query.next())
        {
           i++;
        }
        if(i)
        {
            return true;
        }else
        {
            return false;
        }
    }
}

bool db4Makesi::isExistInTF(QString inTitle)
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from tf where title = \'%1\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        int i=0;
        while(sql_query.next())
        {
           i++;
        }
        if(i)
        {
            return true;
        }else
        {
            return false;
        }
    }
}


QStringList db4Makesi::search(QString inTitle)
{
    struct choiceResult tmp;
    result.clear();
    QSqlQuery sql_query;
    QString select_sql = QString("select * from singleChoice where title like \'%%1%\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return result;
    }
    else
    {
        while(sql_query.next())
        {
            tmp.title=sql_query.value(1).toString();
            tmp.answerA=sql_query.value(2).toString();
            tmp.answerB=sql_query.value(3).toString();
            tmp.answerC=sql_query.value(4).toString();
            tmp.answerD=sql_query.value(5).toString();
            tmp.answer=sql_query.value(6).toString();
            result.append(tmp.title);
            result.append(getRightAnswer(tmp));
        }
    }

    select_sql = QString("select * from multipleChoice where title like \'%%1%\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return result;
    }
    else
    {
            while(sql_query.next())
            {
                tmp.title=sql_query.value(1).toString();
                tmp.answerA=sql_query.value(2).toString();
                tmp.answerB=sql_query.value(3).toString();
                tmp.answerC=sql_query.value(4).toString();
                tmp.answerD=sql_query.value(5).toString();
                tmp.answerE=sql_query.value(6).toString();
                tmp.answer=sql_query.value(7).toString();
                result.append(tmp.title);
                result.append(getRightAnswer(tmp));
            }
    }

    select_sql = QString("select * from tf where title like \'%%1%\'").arg(inTitle);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
        return result;
    }
    else
    {
            while(sql_query.next())
            {
                result.append(sql_query.value(1).toString());
                result.append(sql_query.value(2).toString());
            }
    }
    return result;
}

QString db4Makesi::getRightAnswer(choiceResult inTmp)
{
    QString tmpRtn;
    if(inTmp.answer.contains("A"))
        tmpRtn=tmpRtn+inTmp.answerA;
    if(inTmp.answer.contains("B"))
        tmpRtn=tmpRtn+inTmp.answerB;
    if(inTmp.answer.contains("C"))
        tmpRtn=tmpRtn+inTmp.answerC;
    if(inTmp.answer.contains("D"))
        tmpRtn=tmpRtn+inTmp.answerD;
    if(inTmp.answer.contains("E"))
        tmpRtn=tmpRtn+inTmp.answerE;

    return tmpRtn;
}
