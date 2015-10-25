#ifndef PAUSERULE_H
#define PAUSERULE_H

#include "baserule.h"

class PauseRule: public BaseRule {
 public:
  PauseRule(QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes);
  virtual void calculate();
};

#endif // PAUSERULE_H
