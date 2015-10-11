#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QtWidgets/QWidget>
#include "database/database.h"

namespace Ui {
class AccountWidget;
}

class AccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWidget(QString username, Database * database, QWidget *parent = 0);
    ~AccountWidget();
    void init();
    void loadAccounts();
    void loadIterativeAccounts();

private slots:
    void on_addButton_clicked();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

protected:
    QString username;
    Database *database;

private:
    Ui::AccountWidget *ui;
};

#endif // ACCOUNTWIDGET_H
