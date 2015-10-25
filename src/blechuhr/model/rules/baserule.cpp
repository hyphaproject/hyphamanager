#include "baserule.h"

BaseRule::BaseRule(QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes) {
  this->accounts = accounts;
  this->workingTimes = workingTimes;
}

void BaseRule::calculate() {

}

QList<BaseAccount *> BaseRule::getAccounts() {
  return accounts;
}

QList<WorkingTime *> BaseRule::getWorkingTimes() {
  return workingTimes;
}
