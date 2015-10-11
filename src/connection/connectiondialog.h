#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtWidgets/QDialog>

class Database;
namespace hypha {
namespace handler {
class HandlerLoader;
}
namespace plugin{
class PluginLoader;
}
}

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(hypha::handler::HandlerLoader * handlerLoader, hypha::plugin::PluginLoader * pluginLoader, Database * database, QWidget *parent = 0);
    ~ConnectionDialog();
    void init();

private slots:
    void on_deleteButton_clicked();
    void on_addButton_clicked();

private:
    Ui::ConnectionDialog *ui;
    Database * database;
    hypha::handler::HandlerLoader * handlerLoader;
    hypha::plugin::PluginLoader * pluginLoader;
};

#endif // CONNECTIONDIALOG_H
