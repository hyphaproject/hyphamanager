#ifndef DOOROPENERWIDGET_H
#define DOOROPENERWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItemModel>

#include "database/database.h"
#include "database/userdatabase.h"


namespace Ui {
class DoorOpenerWidget;
}

class DoorOpenerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DoorOpenerWidget(QWidget *parent = 0);
    ~DoorOpenerWidget();
    void setDatabase(Database * database);
    void setUserDatabase(UserDatabase * userDatabase);
    void setId(QString id);
    void loadConfig(QString json);
    void reloadUser();
    QString getConfig();

private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();

private:
    Ui::DoorOpenerWidget *ui;
    Database * database;
    UserDatabase *userDatabase;
    QString id;
    QStandardItemModel listModel;
};

#endif // DOOROPENERWIDGET_H
