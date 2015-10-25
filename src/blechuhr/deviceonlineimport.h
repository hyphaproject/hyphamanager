#ifndef DEVICEONLINEIMPORT_H
#define DEVICEONLINEIMPORT_H

#include "model/workingtime.h"

namespace hypha {
namespace database {
    class Database;
    class UserDatabase;
}
}

class DeviceOnlineImport
{
public:
    DeviceOnlineImport(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase);
    void setUsername(QString username);
    void setDate(QDate date);
    ~DeviceOnlineImport();
    QList<WorkingTime*> getMonth();

protected:
    hypha::database::Database *database;
    hypha::database::UserDatabase *userDatabase;
    QString username;
    QDate date;
    void accumulate(QString device, QString type, QDateTime time);
    void accumulate(QString username, QDateTime start, QDateTime end, QString type);
    void accumulate();
    bool accumulateStop();
    bool accumulateContinue();
    QList<WorkingTime*> stopTime; // first contact starts time and second stops time
    QList<WorkingTime*> continueTime; // first starts and another contact within period continues time ...
    QList<WorkingTime*> times;
};

#endif // DEVICEONLINEIMPORT_H
