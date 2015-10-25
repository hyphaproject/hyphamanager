#ifndef WORKINGTIMEADDDIALOG_H
#define WORKINGTIMEADDDIALOG_H

#include <QtWidgets/QDialog>
#include <QtCore/QDate>
#include "workingtimeitem.h"

namespace hypha {
namespace database {
    class Database;
}
}

namespace Ui {
class WorkingTimeAddDialog;
}

class WorkingTimeAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkingTimeAddDialog(QString username, QDate date, hypha::database::Database * database, QWidget *parent = 0);
    ~WorkingTimeAddDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void init();
    Ui::WorkingTimeAddDialog *ui;
    QString username;
    QDate date;
    hypha::database::Database *database;
    WorkingTimeItem *workingTimeItem;

};

#endif // WORKINGTIMEADDDIALOG_H
