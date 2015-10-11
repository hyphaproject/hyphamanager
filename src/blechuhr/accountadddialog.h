#ifndef ACCOUNTADDDIALOG_H
#define ACCOUNTADDDIALOG_H

#include <QtWidgets/QDialog>
#include "accountitem.h"
#include "database/database.h"

namespace Ui {
class AccountAddDialog;
}

class AccountAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountAddDialog(QString username, QDate date, Database * database, QWidget *parent = 0);
    ~AccountAddDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void init();
    Ui::AccountAddDialog *ui;
    QString username;
    QDate date;
    Database *database;
    AccountItem *accountItem;

    };

#endif // ACCOUNTADDDIALOG_H
