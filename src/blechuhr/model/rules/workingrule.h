#ifndef WORKINGRULE_H
#define WORKINGRULE_H

#include "baserule.h"

class WorkingRule: public BaseRule {
 public:
  WorkingRule(QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes);
  virtual void calculate();
};

#endif // WORKINGRULE_H
