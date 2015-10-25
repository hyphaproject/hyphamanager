#include "account.h"


Account::Account(QString username, QDateTime start, QDateTime end, float amount, hypha::blechuhr::TYPE type, QString name) {
  this->username = username;
  this->start = start;
  this->end = end;
  this->amount = amount;
  this->type = type;
  this->name = name;
}

hypha::blechuhr::TYPE Account::getType() {
  return type;
}
