#include "iterativeaccount.h"


IterativeAccount::IterativeAccount(QString username, QDateTime start, QDateTime end, QTime startTime, QTime endTime, hypha::blechuhr::ITYPE type) {
  this->username = username;
  this->start = start;
  this->end = end;
  this->startTime = startTime;
  this->endTime = endTime;
  this->itype = type;
}

QTime IterativeAccount::getStartTime() {
  return startTime;
}

QTime IterativeAccount::getEndTime() {
  return endTime;
}
