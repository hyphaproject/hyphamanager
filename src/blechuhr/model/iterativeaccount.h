#ifndef ITERATIVEACCOUNT_H
#define ITERATIVEACCOUNT_H
#include <QtCore/QTime>
#include "baseaccount.h"

class IterativeAccount: public BaseAccount
{
public:
    IterativeAccount(QString username, QDateTime start, QDateTime end, QTime startTime, QTime endTime, hypha::blechuhr::ITYPE type = hypha::blechuhr::ITYPE::WORKINGSUN);

    QTime getStartTime();
    QTime getEndTime();
protected:
    QTime startTime;
    QTime endTime;
    hypha::blechuhr::ITYPE itype;
};

#endif // ITERATIVEACCOUNT_H
