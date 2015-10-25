#ifndef BASERULE_H
#define BASERULE_H

#include <QtCore/QList>
#include "../workingtime.h"
#include "../baseaccount.h"


class BaseRule {
  public:
    BaseRule(QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes);
    virtual void calculate();
    QList<BaseAccount *> getAccounts();
    QList<WorkingTime *> getWorkingTimes();

  protected:
    QList<BaseAccount *> accounts;
    QList<WorkingTime *> workingTimes;
};

#endif // BASERULE_H
