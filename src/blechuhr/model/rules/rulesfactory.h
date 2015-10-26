#ifndef RULESFACTORY_H
#define RULESFACTORY_H

#include <QtCore/QList>
#include "../baseaccount.h"
#include "../workingtime.h"
#include "baserule.h"
#include "workingrule.h"
#include "pauserule.h"

class RulesFactory {
  private:
    RulesFactory();
  public:
    static BaseRule *getRule(QString type, QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes);
};

#endif // RULESFACTORY_H
