#ifndef SUMMARYWIDGET_H
#define SUMMARYWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QDate>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>

namespace Ui {
class SummaryWidget;
}

class SummaryWidget : public QWidget {
    Q_OBJECT

  public:
    explicit SummaryWidget(QString username, hypha::database::Database *database, hypha::database::UserDatabase *userDatabase, QWidget *parent = 0);
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
    hypha::database::Database *database;
    hypha::database::UserDatabase *userDatabase;

};

#endif // SUMMARYWIDGET_H
