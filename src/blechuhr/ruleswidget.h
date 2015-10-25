#ifndef RULESWIDGET_H
#define RULESWIDGET_H

#include <QtWidgets/QWidget>
#include <hypha/database/database.h>

namespace Ui {
class RulesWidget;
}

class RulesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RulesWidget(QString username, hypha::database::Database * database, QWidget *parent = 0);
    ~RulesWidget();
    void init();
    void loadRules();

private:
    Ui::RulesWidget *ui;


private slots:
    void on_addButton_clicked();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

protected:
    QString username;
    hypha::database::Database *database;
};

#endif // RULESWIDGET_H
