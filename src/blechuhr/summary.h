#ifndef SUMMARY_H
#define SUMMARY_H

#include <QtCore/QObject>
#include "workingtimealgo.h"

namespace hypha {
namespace database {
    class Database;
    class UserDatabase;
}
}

class Summary
{
public:
    Summary(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase);
    virtual ~Summary();

    void setUsername(QString username);
    void setDate(QDate date);
    virtual float getWorkedHours() = 0;
    virtual bool calculate() = 0;

protected:
    hypha::database::Database *database;
    hypha::database::UserDatabase *userDatabase;
    QString username;
    QDate date;
    WorkingTimeAlgo algo;
};

#endif // SUMMARY_H
