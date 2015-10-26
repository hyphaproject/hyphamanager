#ifndef WORKINGTIMEALGO_H
#define WORKINGTIMEALGO_H

#include <QtCore/QList>
#include <QtCore/QDate>
#include <QtCore/QDateTime>
#include "model/workingtime.h"

namespace hypha {
namespace database {
class Database;
class UserDatabase;
}
}

class WorkingTimeAlgo {
  public:
    WorkingTimeAlgo();
    WorkingTimeAlgo(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase);
    void setUsername(QString username);
    void setDate(QDate date);

    QList<WorkingTime> getDay();
    QList<WorkingTime> getMonth();
    static float getHours(QList<WorkingTime *> times);



  private:
    hypha::database::Database *database;
    hypha::database::UserDatabase *userDatabase;
    QString username;
    QDate date;
    QList<WorkingTime> times;
};

#endif // WORKINGTIMEALGO_H
