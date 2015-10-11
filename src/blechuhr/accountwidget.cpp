#include "accountwidget.h"
#include "ui_accountwidget.h"
#include <QtCore/QDate>
#include <QtCore/QTime>
#include "accountadddialog.h"
#include "accountitem.h"

AccountWidget::AccountWidget(QString username, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    this->username = username;
    this->database = database;
    init();
}

AccountWidget::~AccountWidget()
{
    delete ui;
}

void AccountWidget::init()
{
    loadAccounts();
    loadIterativeAccounts();
}

void AccountWidget::loadAccounts()
{
    ui->listWidget->clear();
    QString queryString = "SELECT id, start, end, type, amount, name FROM account WHERE username = '" + this->username + "' ORDER BY start DESC;";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        hypha::blechuhr::TYPE t = hypha::blechuhr::StringToType(type.toStdString());
        float amount = query.value(4).toFloat();
        QString name = query.value(5).toString();
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountItem *accountItem = new AccountItem(id, username, start, end, t, amount, name,database);
        item->setSizeHint(accountItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, accountItem);
    }
}

void AccountWidget::loadIterativeAccounts()
{
    QString queryString = "SELECT id, start, end, type, starttime, endtime FROM iterativeaccount WHERE username = '" + this->username + "' ORDER BY start DESC;";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        hypha::blechuhr::ITYPE t = hypha::blechuhr::StringToIType(type.toStdString());
        QTime starttime = query.value(4).toTime();
        QTime endtime = query.value(5).toTime();
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountItem *accountItem = new AccountItem(id, username, start, end, t, starttime, endtime, database);
        item->setSizeHint(accountItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, accountItem);
    }
}

void AccountWidget::on_addButton_clicked()
{
    AccountAddDialog aAddDialog(this->username, QDate::currentDate(), database);
    aAddDialog.exec();
    init();
}

void AccountWidget::on_saveButton_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        AccountItem * item = (AccountItem*) ui->listWidget->itemWidget(ui->listWidget->item(i));
        item->save();
    }
    init();
}

void AccountWidget::on_deleteButton_clicked()
{
    AccountItem *item = (AccountItem*) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if(item){
        item->deleteFromDatabase();
        init();
    }
}
