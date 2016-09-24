#ifndef DOOROPENERWIDGET_H
#define DOOROPENERWIDGET_H

#include <QtGui/QStandardItemModel>
#include <QtWidgets/QWidget>

#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>

namespace Ui {
class DoorOpenerWidget;
}

class DoorOpenerWidget : public QWidget {
  Q_OBJECT

 public:
  explicit DoorOpenerWidget(QWidget *parent = 0);
  ~DoorOpenerWidget();
  void setDatabase(hypha::database::Database *database);
  void setUserDatabase(hypha::database::UserDatabase *userDatabase);
  void setId(QString id);
  void loadConfig(QString json);
  void reloadUser();
  QString getConfig();

 private slots:
  void on_deleteButton_clicked();

  void on_addButton_clicked();

 private:
  Ui::DoorOpenerWidget *ui;
  hypha::database::Database *database;
  hypha::database::UserDatabase *userDatabase;
  QString id;
  QStandardItemModel listModel;
};

#endif  // DOOROPENERWIDGET_H
