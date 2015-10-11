#include "deviceonlineimport.h"

DeviceOnlineImport::DeviceOnlineImport(Database *database, UserDatabase *userDatabase)
{
    this->database = database;
    this->userDatabase = userDatabase;
}

void DeviceOnlineImport::setUsername(QString username)
{
    this->username = username;
}

void DeviceOnlineImport::setDate(QDate date)
{
    this->date = date;
}

DeviceOnlineImport::~DeviceOnlineImport()
{

}


QList<WorkingTime*> DeviceOnlineImport::getMonth()
{
    times.clear();
    QString queryString = "SELECT deviceid, time, type FROM deviceonline WHERE MONTH(time) = MONTH('"+date.toString("yyyy-MM-dd")+"') and YEAR(time) = YEAR('"+date.toString("yyyy-MM-dd")+"')";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString device = query.value(0).toString();
        QDateTime time = query.value(1).toDateTime();
        time.setTimeSpec(Qt::UTC);
        QString type = query.value(2).toString();
        accumulate(device, type, time);
    }
    accumulate();
    return times;
}



void DeviceOnlineImport::accumulate(QString device, QString type, QDateTime time)
{
    if(userDatabase->getOwnerOfDevice(device) == username || device == "authuser"+username){
        WorkingTime *wt= new WorkingTime(username, time.toString("yyyy,MM,dd"), time, time);
        if(type == "rfid"){
            this->stopTime.append(wt);
        }else if(type == "wifi"){
            this->continueTime.append(wt);
        }else if(type == "other"){
            this->stopTime.append(wt);
        }
    }
}

void DeviceOnlineImport::accumulate(QString username, QDateTime start, QDateTime end, QString type)
{
    if(type == "working"){
        WorkingTime *wt = new WorkingTime(username, start.toString("yyyy,MM,dd"), start, end);
        this->continueTime.append(wt);
    }
}

void DeviceOnlineImport::accumulate()
{
    accumulateStop();
    foreach(WorkingTime *wt, stopTime){
        times.append(wt);
    }
    while(!accumulateContinue());
    foreach(WorkingTime *wt, continueTime){
        times.append(wt);
    }
}

bool DeviceOnlineImport::accumulateStop()
{
    bool start = true;
    WorkingTime *current;
    QList<WorkingTime*> temp;
    foreach(WorkingTime *wt, stopTime){
        if(start){
            current = new WorkingTime(wt);
            start = false;
        }else{
            if(current->getStart().date().day() != wt->getStart().date().day()){
                // day ends at midnight
                current->getEnd().time().setHMS(23,59,59);
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

bool DeviceOnlineImport::accumulateContinue()
{
    foreach(WorkingTime *wt, continueTime){
        foreach(WorkingTime *wt2, continueTime){
            if(wt->belongsTo(*wt2, 300)){
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

