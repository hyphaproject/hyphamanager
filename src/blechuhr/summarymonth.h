#ifndef SUMMARYMONTH_H
#define SUMMARYMONTH_H

#include "summary.h"

namespace hypha {
namespace database {
class Database;
class UserDatabase;
}
}

class SummaryMonth: public Summary {
 public:
  SummaryMonth(hypha::database::Database *database, hypha::database::UserDatabase *userDatabase);
  ~SummaryMonth();

  float getWorkedHours();
  bool calculate();

};

#endif // SUMMARYMONTH_H
