#ifndef WORKINGTIMEALGO_H
#define WORKINGTIMEALGO_H

#include <QtCore/QList>
#include <QtCore/QDate>
#include <QtCore/QDateTime>
#include "model/workingtime.h"
#include "../database/database.h"
#include "../database/userdatabase.h"

class WorkingTimeAlgo
{
public:
    WorkingTimeAlgo();
    WorkingTimeAlgo(Database *database, UserDatabase *userDatabase);
    void setUsername(QString username);
    void setDate(QDate date);

    QList<WorkingTime> getDay();
    QList<WorkingTime> getMonth();
    static float getHours(QList<WorkingTime*> times);



private:
    Database *database;
    UserDatabase *userDatabase;
    QString username;
    QDate date;
    QList<WorkingTime> times;
};

#endif // WORKINGTIMEALGO_H
