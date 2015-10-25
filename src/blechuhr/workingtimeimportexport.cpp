#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include "workingtimeimportexport.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDebug>

WorkingTimeImportExport::WorkingTimeImportExport(hypha::database::Database *database, QString username, QString file)
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

    Poco::Data::Statement statement = database->getStatement();
    if(date == 0)
        statement << "SELECT id, start, end, type FROM workingtime WHERE username = '" + username.toStdString() + "';";
    else
        statement << "SELECT id, start, end, type FROM workingtime WHERE username = '" + username.toStdString() + "' AND DATE(start) = '"
                     + date->toString("yyyy-MM-dd").toStdString() + "';";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        std::string id = rs[0].convert<std::string>();
        std::string start = rs[1].convert<std::string>();
        QDateTime startTime = QDateTime::fromString(QString::fromStdString(start));
        std::string end = rs[2].convert<std::string>();
        QDateTime endTime = QDateTime::fromString(QString::fromStdString(end));
        std::string type = rs[3].convert<std::string>();

        startTime.setTimeSpec(Qt::UTC);
        endTime.setTimeSpec(Qt::UTC);

        WorkingTime *wt = new WorkingTime(username, startTime.toString(), startTime, endTime, QString::fromStdString(type));
        returnList.append(wt);

        more = rs.moveNext();
    }

    QString queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + username + "';";
    if(date != 0){
        queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + username + "' AND DATE(start) = '"
                + date->toString("yyyy-MM-dd")+"';";
    }

    return returnList;
}

void WorkingTimeImportExport::toDatabase(QList<WorkingTime*> list, QDate *date)
{
    for(WorkingTime *wt: list ){
        Poco::Data::Statement statement = database->getStatement();
        statement << "insert into workingtime(username, type, start, end) values(:username, :type, :start, :end);",
                Poco::Data::use(wt->getUsername().toStdString()), Poco::Data::use(wt->getType().toStdString()),
                Poco::Data::use(wt->getStart().toUTC().toString().toStdString()), Poco::Data::use(wt->getEnd().toUTC().toString().toStdString());
        statement.execute();
    }
}

