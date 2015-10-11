#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QtWidgets/QWidget>
#include <QtCore/QDateTime>
#include "../database/database.h"
#include "model/type.h"

namespace Ui {
class AccountItem;
}

class AccountItem : public QWidget
{
    Q_OBJECT

public:
    explicit AccountItem(QWidget *parent = 0);
    AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, Database *database, QWidget *parent = 0);
    AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, Database *database, QWidget *parent = 0);
    AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, Database *database, QWidget *parent = 0);
    AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, Database *database, QWidget *parent = 0);
    ~AccountItem();

    void save();
    void deleteFromDatabase();

private slots:

    void on_iterativeCheckBox_clicked(bool checked);
    void updateElements();

private:
    bool isIterative;
    void init();
    void initType();
    Ui::AccountItem *ui;
    QString id;
    QString username;
    QDateTime start;
    QDateTime end;
    hypha::blechuhr::TYPE type;
    hypha::blechuhr::ITYPE itype;
    QString name;
    float amount;
    QTime starttime;
    QTime endtime;
    Database *database;
};

#endif // ACCOUNTITEM_H
