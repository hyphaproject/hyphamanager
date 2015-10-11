#ifndef WORKINGTIMEIMPORTEXPORT_H
#define WORKINGTIMEIMPORTEXPORT_H

#include <QtCore/QString>
#include <QtCore/QDate>
#include <QtCore/QList>
#include "../database/database.h"
#include "model/workingtime.h"

class WorkingTimeImportExport
{
public:
    WorkingTimeImportExport(Database *database, QString username, QString file);
    WorkingTimeImportExport(QString username,QList<WorkingTime*> times, QString file);
    ~WorkingTimeImportExport();
    void importData(QDate *date = 0);
    void exportDataFromDatabase(QDate *date = 0);
    void exportData();

protected:
    QString username;
    QString file;
    Database * database;
    QList<WorkingTime*> times;

    QList<WorkingTime*> fromDatabase(QDate * date);
    void toDatabase(QList<WorkingTime*> list, QDate *date);

};

#endif // WORKINGTIMEIMPORTEXPORT_H
