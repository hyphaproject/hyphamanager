#ifndef WORKINGTIME_H
#define WORKINGTIME_H

#include <QtCore/QString>
#include <QtCore/QDateTime>

class WorkingTime
{
public:
    WorkingTime(const WorkingTime &workingTime);
    WorkingTime(WorkingTime*workingTime);
    WorkingTime(QString username, QString date, QDateTime start, QDateTime end, QString type = "working");

    QString toAddString(bool onlyTime = false);

    bool belongsTo(WorkingTime &other, int seconds);
    void accumulate(WorkingTime &other);

    bool operator== (WorkingTime other) {
        return this->username == other.username && this->date == other.date && this->start == other.start && this->end == other.end;
    }

    static bool before(WorkingTime *w1, WorkingTime *w2);

    bool sameDay(WorkingTime &other);

    float hours();

    static WorkingTime fromCSV(QString username, QString csv, bool dateExtra = false);
    static WorkingTime fromCSV(QString csv, bool withUsername = false);
    static WorkingTime fromCSV(QString csv, int iUsername, int iDate, int iFrom, int iTo, int iType = -1);
    static WorkingTime fromCSVextraDate(QString csv, bool withUsername = false);
    QString toCSV(bool withUsername = false);

    void setUsername(QString username);

    QString getUsername();
    QString getType();
    QDateTime getStart();
    QDateTime getEnd();

private:
    QString username;
    QString date;
    QDateTime start;
    QDateTime end;
    QString type;

};

#endif // WORKINGTIME_H
