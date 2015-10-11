#ifndef SUMMARYMONTH_H
#define SUMMARYMONTH_H

#include "summary.h"

class SummaryMonth: public Summary
{
public:
    SummaryMonth(Database *database, UserDatabase *userDatabase);
    ~SummaryMonth();

    float getWorkedHours();
    bool calculate();

};

#endif // SUMMARYMONTH_H
