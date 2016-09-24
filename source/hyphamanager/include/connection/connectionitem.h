#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QtWidgets/QWidget>

namespace hypha {
namespace database {
class Database;
}
}

namespace Ui {
class ConnectionItem;
}

class ConnectionItem : public QWidget {
  Q_OBJECT

 public:
  explicit ConnectionItem(QString id, QString handlerId, QString pluginId,
                          hypha::database::Database *database,
                          QWidget *parent = 0);
  ~ConnectionItem();

  void deleteFromDatabase();
  void init();

 private:
  Ui::ConnectionItem *ui;
  QString id;
  QString handlerId;
  QString pluginId;
  hypha::database::Database *database;
};

#endif  // CONNECTIONITEM_H
