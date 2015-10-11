#ifndef WORKINGTIMEADDDIALOG_H
#define WORKINGTIMEADDDIALOG_H

#include <QtWidgets/QDialog>
#include <QtCore/QDate>
#include "workingtimeitem.h"
#include "../database/database.h"

namespace Ui {
class WorkingTimeAddDialog;
}

class WorkingTimeAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkingTimeAddDialog(QString username, QDate date, Database * database, QWidget *parent = 0);
    ~WorkingTimeAddDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void init();
    Ui::WorkingTimeAddDialog *ui;
    QString username;
    QDate date;
    Database *database;
    WorkingTimeItem *workingTimeItem;

};

#endif // WORKINGTIMEADDDIALOG_H
