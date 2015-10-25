#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "baseaccount.h"


class Account: public BaseAccount {
  public:
    Account(QString username, QDateTime start, QDateTime end, float amount, hypha::blechuhr::TYPE type = hypha::blechuhr::TYPE::WORKING, QString name = "");

    QString getUsername();
    hypha::blechuhr::TYPE getType();
    QDateTime getStart();
    QDateTime getEnd();
    float getAmount();

  protected:
    float amount;
    hypha::blechuhr::TYPE type;
    QString name;
};

#endif // ACCOUNT_H
