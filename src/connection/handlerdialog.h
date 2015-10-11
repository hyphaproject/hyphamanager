#ifndef HANDLERDIALOG_H
#define HANDLERDIALOG_H

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
class HandlerDialog;
}

class HandlerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandlerDialog(hypha::handler::HandlerLoader * handlerLoader, Database * database, QWidget *parent = 0);
    ~HandlerDialog();
        void init();

private slots:
        void on_buttonBox_accepted();

private:
    Ui::HandlerDialog *ui;
    hypha::handler::HandlerLoader *handlerLoader;
    Database *database;
};

#endif // HANDLERDIALOG_H
