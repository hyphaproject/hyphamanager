#include "workingtime.h"
#include <QtCore/QStringList>
#include <QDebug>

WorkingTime::WorkingTime(const WorkingTime &workingTime) {
    this->username = workingTime.username;
    this->date = workingTime.date;
    this->start = workingTime.start;
    this->end = workingTime.end;
    this->type = workingTime.type;
}

WorkingTime::WorkingTime(WorkingTime *workingTime) {
    this->username = workingTime->username;
    this->date = workingTime->date;
    this->start = workingTime->start;
    this->end = workingTime->end;
    this->type = workingTime->type;
}

WorkingTime::WorkingTime(QString username, QString date, QDateTime start, QDateTime end, QString type) {
    this->username = username;
    this->date = date;
    this->start = start;
    this->end = end;
    this->type = type;
}

QString WorkingTime::toAddString(bool onlyTime) {
    return "addData('" + date + "', new Date(" + start.toLocalTime().addMonths(-1).toString(onlyTime ? "2000,00,01,hh,mm,ss" : "yyyy,MM,dd,hh,mm,ss") +
           "), new Date(" + end.toLocalTime().addMonths(-1).toString(onlyTime ? "2000,00," + QString::number(1 + end.date().day() - start.date().day()) + ",hh,mm,ss" : "yyyy,MM,dd,hh,mm,ss") + "))";
}

bool WorkingTime::belongsTo(WorkingTime &other, int seconds) {
    return this != &other && this->username == other.username
           && ((this->end < other.start
                && (other.start.toMSecsSinceEpoch() - this->end.toMSecsSinceEpoch() < seconds * 1000))
               || (this->start > other.start && this->end < other.end)
               || (this->start < other.start && this->end > other.end)); // less than X seconds diff
}

void WorkingTime::accumulate(WorkingTime &other) {
    if (this->start > other.start) this->start = other.start;
    if (this->end < other.end) this->end = other.end;
}

bool WorkingTime::before(WorkingTime *w1, WorkingTime *w2) {
    return w1->getStart() < w2->getStart();
}

bool WorkingTime::sameDay(WorkingTime &other) {
    return this->start.date() == other.start.date() && this->end.date() == other.end.date();
}

float WorkingTime::hours() {
    return (end.toMSecsSinceEpoch() - start.toMSecsSinceEpoch()) / 3600000.0f;
}

WorkingTime WorkingTime::fromCSV(QString username, QString csv, bool dateExtra) {
    if (dateExtra) {

    } else {
        return fromCSV(username + ";" + csv, false);
    }
}

/**
 * @brief WorkingTime::fromCSV
 * @param csv
 * @return
 *
 * Format is: username,start,end,(type=working)
 */
WorkingTime WorkingTime::fromCSV(QString csv, bool withUsername) {
    QStringList vals = csv.split(';');
    QString username = "unknown";
    QString type = "working";
    if (withUsername) {
        username = vals.at(0);
        if (vals.size() > 3) {
            type = vals.at(3);
        }
    } else {
        if (vals.size() > 2) {
            type = vals.at(2);
        }
    }
    QDateTime start = QDateTime::fromString(vals.at(0 + withUsername ? 1 : 0), "dd.MM.yyyy hh:mm");
    QDateTime end = QDateTime::fromString(vals.at(1 + withUsername ? 1 : 0), "dd.MM.yyyy hh:mm");
    return WorkingTime(username, start.toString(), start, end, type);
}

WorkingTime WorkingTime::fromCSV(QString csv, int iUsername, int iDate, int iFrom, int iTo, int iType) {
    QStringList vals = csv.split(';');
    QString username = (iUsername == -1) ? "unknown" : vals.at(iUsername);
    QString sStart = (iDate == -1) ? vals.at(iFrom) : vals.at(iDate) + " " + vals.at(iFrom);
    QString sEnd = (iDate == -1) ? vals.at(iTo) : vals.at(iDate) + " " + vals.at(iTo);
    QDateTime start = QDateTime::fromString(sStart, "dd.MM.yyyy hh:mm");
    QDateTime end = QDateTime::fromString(sEnd, "dd.MM.yyyy hh:mm");
    QString type = (iType == -1) ? "working" : vals.at(iType);
    return WorkingTime(username, start.toString(), start, end, type);

}

WorkingTime WorkingTime::fromCSVextraDate(QString csv, bool withUsername) {
    QStringList vals = csv.split(';');
    QString username = "unknown";
    QString type = "working";

    if (withUsername) {
        username = vals.at(0);
        if (vals.size() > 4) {
            type = vals.at(4);
        }
    } else {
        if (vals.size() > 3) {
            type = vals.at(3);
        }
    }
    QString date = vals.at(0 + withUsername ? 1 : 0);
    qDebug() << date + " " + vals.at(1 + withUsername ? 1 : 0);
    QDateTime start = QDateTime::fromString(date + " " + vals.at(1 + withUsername ? 1 : 0), "dd.MM.yyyy hh:mm");
    QDateTime end = QDateTime::fromString(date + " " + vals.at(2 + withUsername ? 1 : 0), "dd.MM.yyyy hh:mm");
    return WorkingTime(username, start.toString(), start, end, type);
}

/**
 * @brief WorkingTime::toCSV
 * @param withUsername
 * @return
 *
 * Format is: username,start,end,(type=working)
 */
QString WorkingTime::toCSV(bool withUsername) {
    QString returnStr = withUsername ? username + ";" : "";
    returnStr += start.toLocalTime().toString("dd.MM.yyyy") + ";";
    returnStr += start.toLocalTime().toString("hh:mm") + ";";
    returnStr += end.toLocalTime().toString("hh:mm") + ";";
    returnStr += type;
    return returnStr;
}

void WorkingTime::setUsername(QString username) {
    this->username = username;
}

QString WorkingTime::getUsername() {
    return username;
}

QString WorkingTime::getType() {
    return type;
}

QDateTime WorkingTime::getStart() {
    return start;
}

QDateTime WorkingTime::getEnd() {
    return end;
}
