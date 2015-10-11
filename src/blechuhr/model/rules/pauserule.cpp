#include "pauserule.h"

PauseRule::PauseRule(QList<BaseAccount *> accounts, QList<WorkingTime *> workingTimes): BaseRule(accounts, workingTimes)
{

}

void PauseRule::calculate()
{
    QList<WorkingTime *> toAdd;
    for(WorkingTime *wt: workingTimes){
        if(wt->hours() > 6){
            QDateTime start = QDateTime(wt->getStart().addSecs(6*60*60));
            QDateTime end = QDateTime(wt->getStart().addSecs(6*60*60+30*60));
            WorkingTime *workingTime = new WorkingTime(wt->getUsername(), "", start, end, "pause");
            toAdd.append(workingTime);
        }
    }
    workingTimes.append(toAdd);
}
