#ifndef RULESITEM_H
#define RULESITEM_H

#include <QtWidgets/QWidget>
#include <QtCore/QDateTime>
#include "model/type.h"

namespace hypha {
namespace database {
class Database;
}
}

namespace Ui {
class RulesItem;
}

class RulesItem : public QWidget {
  Q_OBJECT

 public:
  explicit RulesItem(QWidget *parent = 0);
  RulesItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, hypha::database::Database *database, QWidget *parent = 0);
  RulesItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, hypha::database::Database *database, QWidget *parent = 0);
  ~RulesItem();


  void save();
  void deleteFromDatabase();

 private:
  void init();
  void initType();
  Ui::RulesItem *ui;
  QString id;
  QString username;
  QDateTime start;
  QDateTime end;
  hypha::blechuhr::RTYPE type;
  hypha::database::Database *database;
};

#endif // RULESITEM_H
