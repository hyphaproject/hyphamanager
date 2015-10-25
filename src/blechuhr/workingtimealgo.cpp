#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "workingtimealgo.h"

WorkingTimeAlgo::WorkingTimeAlgo() {

}

WorkingTimeAlgo::WorkingTimeAlgo(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase) {
  this->database = database;
  this->userDatabase = userDatabase;
}

void WorkingTimeAlgo::setUsername(QString username) {
  this->username = username;
}

void WorkingTimeAlgo::setDate(QDate date) {
  this->date = date;
}

QList<WorkingTime> WorkingTimeAlgo::getDay() {
  times.clear();

  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id, start, end, type FROM workingtime WHERE username = '" + this->username.toStdString() +
            "' AND DATE(start) = '" + date.toString("yyyy-MM-dd").toStdString() + "'";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    std::string id = rs[0].convert<std::string>();
    std::string start = rs[1].convert<std::string>();
    QDateTime startTime = QDateTime::fromString(QString::fromStdString(start));
    std::string end = rs[2].convert<std::string>();
    QDateTime endTime = QDateTime::fromString(QString::fromStdString(end));
    std::string type = rs[3].convert<std::string>();

    startTime.setTimeSpec(Qt::UTC);
    endTime.setTimeSpec(Qt::UTC);

    WorkingTime wt(username, startTime.toLocalTime().toString("hh:00"), startTime, endTime, QString::fromStdString(type));
    times.append(wt);

    more = rs.moveNext();
  }
  return times;
}

QList<WorkingTime> WorkingTimeAlgo::getMonth() {
  times.clear();

  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id, start, end, type FROM workingtime WHERE username = '" + this->username.toStdString() +
            "' AND DATE(start) = '" + date.toString("yyyy-MM-dd").toStdString() + "'";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    std::string id = rs[0].convert<std::string>();
    std::string start = rs[1].convert<std::string>();
    QDateTime startTime = QDateTime::fromString(QString::fromStdString(start));
    std::string end = rs[2].convert<std::string>();
    QDateTime endTime = QDateTime::fromString(QString::fromStdString(end));
    std::string type = rs[3].convert<std::string>();

    startTime.setTimeSpec(Qt::UTC);
    endTime.setTimeSpec(Qt::UTC);

    WorkingTime wt(username, startTime.toString("dd. MMM"), startTime, endTime, QString::fromStdString(type));
    times.append(wt);

    more = rs.moveNext();
  }

  return times;
}

float WorkingTimeAlgo::getHours(QList<WorkingTime *> times) {
  float hours = 0.0f;
  foreach(WorkingTime * wt, times) {
    if (wt->getType() == "working")
      hours += wt->hours();
    if (wt->getType() == "pause")
      hours -= wt->hours();
  }
  return hours;
}
