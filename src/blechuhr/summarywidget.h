#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QDate>
#include "../database/database.h"
#include "../database/userdatabase.h"

namespace Ui {
class SummaryWidget;
}

class SummaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SummaryWidget(QString username, Database * database, UserDatabase * userDatabase, QWidget *parent = 0);
    ~SummaryWidget();

public slots:
    void reloadSummary();
    void calculateWorkingHours();
    QDate getSelectedDate();

private slots:
    void on_dateEdit_editingFinished();

private:
    Ui::SummaryWidget *ui;
    QString username;
    Database *database;
    UserDatabase * userDatabase;

};

#endif // SUMMARYWIDGET_H
