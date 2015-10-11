#ifndef SUMMARY_H
#define SUMMARY_H

#include "../database/database.h"
#include "../database/userdatabase.h"
#include <QtCore/QObject>
#include "workingtimealgo.h"

class Summary
{
public:
    Summary(Database *database, UserDatabase *userDatabase);
    virtual ~Summary();

    void setUsername(QString username);
    void setDate(QDate date);
    virtual float getWorkedHours() = 0;
    virtual bool calculate() = 0;

protected:
    Database *database;
    UserDatabase *userDatabase;
    QString username;
    QDate date;
    WorkingTimeAlgo algo;
};

#endif // SUMMARY_H
