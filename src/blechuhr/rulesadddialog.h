#ifndef RULESADDDIALOG_H
#define RULESADDDIALOG_H

#include <QtWidgets/QDialog>
#include "rulesitem.h"

namespace hypha {
namespace database {
    class Database;
}
}

namespace Ui {
class RulesAddDialog;
}

class RulesAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RulesAddDialog(QString username, QDate date, hypha::database::Database * database, QWidget *parent = 0);
    ~RulesAddDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void init();
    Ui::RulesAddDialog *ui;
    QString username;
    QDate date;
    hypha::database::Database *database;
    RulesItem *rulesItem;
};

#endif // RULESADDDIALOG_H
