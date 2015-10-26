#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "deviceonlineimport.h"

DeviceOnlineImport::DeviceOnlineImport(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase) {
    this->database = database;
    this->userDatabase = userDatabase;
}

void DeviceOnlineImport::setUsername(QString username) {
    this->username = username;
}

void DeviceOnlineImport::setDate(QDate date) {
    this->date = date;
}

DeviceOnlineImport::~DeviceOnlineImport() {

}

QList<WorkingTime *> DeviceOnlineImport::getMonth() {
    times.clear();
    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT deviceid, time, type FROM deviceonline WHERE MONTH(time) = MONTH('" + date.toString("yyyy-MM-dd").toStdString()
              + "') and YEAR(time) = YEAR('" + date.toString("yyyy-MM-dd").toStdString() + "')";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
        std::string device = rs[0].convert<std::string>();
        std::string time = rs[1].convert<std::string>();
        QDateTime datetime = QDateTime::fromString(QString::fromStdString(time));
        std::string type = rs[2].convert<std::string>();
        datetime.setTimeSpec(Qt::UTC);
        accumulate(QString::fromStdString(device), QString::fromStdString(type), datetime);

        more = rs.moveNext();
    }
    accumulate();
    return times;
}

void DeviceOnlineImport::accumulate(QString device, QString type, QDateTime time) {
    if (userDatabase->getOwnerOfDevice(device.toStdString()) == username.toStdString() || device.toStdString() == "authuser" + username.toStdString()) {
        WorkingTime *wt = new WorkingTime(username, time.toString("yyyy,MM,dd"), time, time);
        if (type == "rfid") {
            this->stopTime.append(wt);
        } else if (type == "wifi") {
            this->continueTime.append(wt);
        } else if (type == "other") {
            this->stopTime.append(wt);
        }
    }
}

void DeviceOnlineImport::accumulate(QString username, QDateTime start, QDateTime end, QString type) {
    if (type == "working") {
        WorkingTime *wt = new WorkingTime(username, start.toString("yyyy,MM,dd"), start, end);
        this->continueTime.append(wt);
    }
}

void DeviceOnlineImport::accumulate() {
    accumulateStop();
    for (WorkingTime *wt : stopTime) {
        times.append(wt);
    }
    while (!accumulateContinue());
    for (WorkingTime *wt : continueTime) {
        times.append(wt);
    }
}

bool DeviceOnlineImport::accumulateStop() {
    bool start = true;
    WorkingTime *current;
    QList<WorkingTime *> temp;
    for (WorkingTime *wt : stopTime) {
        if (start) {
            current = new WorkingTime(wt);
            start = false;
        } else {
            if (current->getStart().date().day() != wt->getStart().date().day()) {
                // day ends at midnight
                current->getEnd().time().setHMS(23, 59, 59);
                temp.append(current);
                current = new WorkingTime(wt);
                start = false;
                continue;
            }
            current->accumulate(*wt);
            temp.append(current);
            start = true;
        }
    }
    stopTime = temp;
    return true;
}

bool DeviceOnlineImport::accumulateContinue() {
    for (WorkingTime *wt : continueTime) {
        for (WorkingTime *wt2 : continueTime) {
            if (wt->belongsTo(*wt2, 300)) {
                WorkingTime *wt1 = new WorkingTime(wt);
                wt1->accumulate(*wt2);
                continueTime.removeAll(wt);
                continueTime.removeAll(wt2);
                continueTime.append(wt1);
                return false;
            }
        }
    }
    return true;
}
