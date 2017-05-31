// Copyright (c) 2015-2016 Hypha
#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtWidgets/QDialog>

namespace hypha {
namespace plugin {
class PluginLoader;
}
namespace database {
class Database;
}
}

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog {
  Q_OBJECT

 public:
  explicit ConnectionDialog(hypha::plugin::PluginLoader *pluginLoader,
                            hypha::database::Database *database,
                            QWidget *parent = 0);
  ~ConnectionDialog();
  void init();

 private slots:
  void on_deleteButton_clicked();
  void on_addButton_clicked();

 private:
  Ui::ConnectionDialog *ui;
  hypha::database::Database *database;
  hypha::plugin::PluginLoader *pluginLoader;
};

#endif  // CONNECTIONDIALOG_H
