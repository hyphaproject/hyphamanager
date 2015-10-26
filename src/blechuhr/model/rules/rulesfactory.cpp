#include "rulesfactory.h"

RulesFactory::RulesFactory() {
}

BaseRule *RulesFactory::getRule(QString type, QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes) {
    if (type == "working") {
        return new WorkingRule(accounts, workingTimes);
    }
    if (type == "pause") {
        return new PauseRule(accounts, workingTimes);
    } else {
        return 0;
    }
}
