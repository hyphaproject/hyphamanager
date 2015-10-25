#ifndef BASEACCOUNT_H
#define BASEACCOUNT_H

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include "type.h"

class BaseAccount {
 public:
  BaseAccount();

  QString getUsername();
  QDateTime getStart();
  QDateTime getEnd();

 protected:
  QString username;
  QDateTime start;
  QDateTime end;
};

#endif // BASEACCOUNT_H
