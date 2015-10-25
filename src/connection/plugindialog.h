#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QtWidgets/QDialog>

namespace hypha {
namespace handler {
class HandlerLoader;
}
namespace plugin{
class PluginLoader;
}
namespace database{
class Database;
}
}

namespace Ui {
class PluginDialog;
}

class PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(hypha::plugin::PluginLoader * pluginLoader, hypha::database::Database * database, QWidget *parent = 0);
    ~PluginDialog();
    void init();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PluginDialog *ui;
    hypha::plugin::PluginLoader *pluginLoader;
    hypha::database::Database *database;
};

#endif // PLUGINDIALOG_H
