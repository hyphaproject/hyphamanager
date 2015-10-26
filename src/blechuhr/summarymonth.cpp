#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "summarymonth.h"
#include "workingtimealgo.h"
#include "model/workingtime.h"

SummaryMonth::SummaryMonth(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase)
    : Summary(database, userDatabase) {
}

SummaryMonth::~SummaryMonth() {

}

float SummaryMonth::getWorkedHours() {
    float hours = 0;
    foreach(WorkingTime wt, algo.getMonth()) {
        if (wt.getType() == "working")
            hours += wt.hours();
    }
    return hours;
}

bool SummaryMonth::calculate() {
    algo = WorkingTimeAlgo(database, userDatabase);
    algo.setUsername(username);
    algo.setDate(date);
    return true;
}
