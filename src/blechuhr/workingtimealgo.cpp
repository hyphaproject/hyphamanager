#include "workingtimealgo.h"
#include <QDebug>
#include <QtSql/QSqlError>


WorkingTimeAlgo::WorkingTimeAlgo()
{

}

WorkingTimeAlgo::WorkingTimeAlgo(Database *database, UserDatabase *userDatabase)
{
    this->database = database;
    this->userDatabase = userDatabase;
}

void WorkingTimeAlgo::setUsername(QString username)
{
    this->username = username;
}

void WorkingTimeAlgo::setDate(QDate date)
{
    this->date = date;
}

QList<WorkingTime> WorkingTimeAlgo::getDay()
{
    times.clear();
    QString queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + this->username +
            "' AND DATE(start) = '" + date.toString("yyyy-MM-dd") + "'";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        WorkingTime wt(username, start.toLocalTime().toString("hh:00"), start, end, type);
        times.append(wt);
    }
    return times;
}

QList<WorkingTime> WorkingTimeAlgo::getMonth()
{
    times.clear();
    QString queryString = "SELECT id, start, end, type FROM workingtime WHERE username = '" + this->username +
            "' AND MONTH(start) = MONTH('"+date.toString("yyyy-MM-dd")+"') and YEAR(start) = YEAR('"+date.toString("yyyy-MM-dd")+"')";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        WorkingTime wt(username, start.toString("dd. MMM"), start, end, type);
        times.append(wt);
    }
    return times;
}

float WorkingTimeAlgo::getHours(QList<WorkingTime*> times)
{
    float hours = 0.0f;
    foreach(WorkingTime *wt, times){
        if(wt->getType() == "working")
            hours += wt->hours();
        if(wt->getType() == "pause")
            hours -= wt->hours();
    }
    return hours;
}
