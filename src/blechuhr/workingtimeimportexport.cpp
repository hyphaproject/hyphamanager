#include "workingtimeimportexport.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDebug>

WorkingTimeImportExport::WorkingTimeImportExport(Database *database, QString username, QString file)
{
    this->database = database;
    this->username = username;
    this->file = file;
}

WorkingTimeImportExport::WorkingTimeImportExport(QString username, QList<WorkingTime*> times, QString file)
{
    this->username = username;
    this->file = file;
    this->times = times;
}

WorkingTimeImportExport::~WorkingTimeImportExport()
{

}

void WorkingTimeImportExport::importData(QDate *date)
{
    QList<WorkingTime*> data;
    QFile f(file);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inStream(&f);
    QString header = inStream.readLine();
    QStringList l = header.split(";");
    int iDate = l.indexOf("date");
    int iFrom = l.indexOf("from");
    int iTo = l.indexOf("to");
    int iType = l.indexOf("type");
    while (!inStream.atEnd())
    {
        QString line = inStream.readLine();
        WorkingTime *wt = new WorkingTime(WorkingTime::fromCSV(line,-1,iDate,iFrom,iTo,iType));
        wt->setUsername(username);
        data.append(wt);
    }
    f.close();
    toDatabase(data, date);
}

/**
 * @brief WorkingTimeImportExport::exportData
 * @param date
 * Exports data of a given month into a csv file.
 */
void WorkingTimeImportExport::exportDataFromDatabase(QDate * date)
{
    times.clear();
    foreach(WorkingTime *wt, fromDatabase(date)){
        times.append(wt);
    }
    exportData();
    //toDatabase(data, date);
}

void WorkingTimeImportExport::exportData()
{
    QFile f(file);
    f.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream outStream(&f);
    outStream << QObject::tr("date;from;to;type") << "\n";
    foreach(WorkingTime *wt, times){
        outStream << wt->toCSV() << "\n";
    }
    f.close();
}

QList<WorkingTime*> WorkingTimeImportExport::fromDatabase(QDate * date)
{
    QList<WorkingTime*> returnList;
    QString queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + username + "';";
    if(date != 0){
        queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + username + "' AND DATE(start) = '"
                + date->toString("yyyy-MM-dd")+"';";
    }
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        WorkingTime *wt = new WorkingTime(username, start.toString(), start, end, type);
        returnList.append(wt);
    }
    return returnList;
}

void WorkingTimeImportExport::toDatabase(QList<WorkingTime*> list, QDate *date)
{
    QSqlQuery query = database->getQuery();
    foreach(WorkingTime *wt, list ){
        query.prepare("insert into workingtime(username, type, start, end) values(:username, :type, :start, :end);");
        query.bindValue(":username", wt->getUsername());
        query.bindValue(":type", wt->getType());
        query.bindValue(":start", wt->getStart().toUTC());
        query.bindValue(":end", wt->getEnd().toUTC());
        query.exec();
    }
}

