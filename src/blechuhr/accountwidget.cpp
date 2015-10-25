#include <QtCore/QDate>
#include <QtCore/QTime>
#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include "accountwidget.h"
#include "ui_accountwidget.h"
#include "accountadddialog.h"
#include "accountitem.h"

AccountWidget::AccountWidget(QString username, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountWidget) {
    ui->setupUi(this);
    this->username = username;
    this->database = database;
    init();
}

AccountWidget::~AccountWidget() {
    delete ui;
}

void AccountWidget::init() {
    loadAccounts();
    loadIterativeAccounts();
}

void AccountWidget::loadAccounts() {
    ui->listWidget->clear();

    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT id, start, end, type, amount, name FROM account WHERE username = '" + this->username.toStdString() + "' ORDER BY start DESC;";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        std::string id = rs[0].convert<std::string>();
        std::string start = rs[1].convert<std::string>();
        QDateTime startTime = QDateTime::fromString(QString::fromStdString(start));
        std::string end = rs[2].convert<std::string>();
        QDateTime endTime = QDateTime::fromString(QString::fromStdString(end));
        std::string type = rs[3].convert<std::string>();

        startTime.setTimeSpec(Qt::UTC);
        endTime.setTimeSpec(Qt::UTC);

        hypha::blechuhr::TYPE t = hypha::blechuhr::StringToType(type);
        float amount = rs[4].convert<float>();
        std::string name = rs[5].convert<std::string>();
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountItem *accountItem = new AccountItem(QString::fromStdString(id), username, startTime,
                endTime, t, amount, QString::fromStdString(name), database);
        item->setSizeHint(accountItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, accountItem);
        more = rs.moveNext();
    }
}

void AccountWidget::loadIterativeAccounts() {
    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT id, start, end, type, starttime, endtime FROM iterativeaccount WHERE username = '" + this->username.toStdString() + "' ORDER BY start DESC;";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        std::string id = rs[0].convert<std::string>();
        std::string start = rs[1].convert<std::string>();
        QDateTime startDateTime = QDateTime::fromString(QString::fromStdString(start));
        std::string end = rs[2].convert<std::string>();
        QDateTime endDateTime = QDateTime::fromString(QString::fromStdString(end));
        std::string type = rs[3].convert<std::string>();

        startDateTime.setTimeSpec(Qt::UTC);
        endDateTime.setTimeSpec(Qt::UTC);

        hypha::blechuhr::ITYPE t = hypha::blechuhr::StringToIType(type);
        std::string start_time = rs[4].convert<std::string>();
        QTime starttime = QTime::fromString(QString::fromStdString(start_time));
        std::string end_time = rs[5].convert<std::string>();
        QTime endtime = QTime::fromString(QString::fromStdString(end_time));

        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountItem *accountItem = new AccountItem(QString::fromStdString(id), username, startDateTime, endDateTime
                , t, starttime, endtime, database);
        item->setSizeHint(accountItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, accountItem);
        more = rs.moveNext();
    }
}

void AccountWidget::on_addButton_clicked() {
    AccountAddDialog aAddDialog(this->username, QDate::currentDate(), database);
    aAddDialog.exec();
    init();
}

void AccountWidget::on_saveButton_clicked() {
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        AccountItem * item = (AccountItem*) ui->listWidget->itemWidget(ui->listWidget->item(i));
        item->save();
    }
    init();
}

void AccountWidget::on_deleteButton_clicked() {
    AccountItem *item = (AccountItem*) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if(item) {
        item->deleteFromDatabase();
        init();
    }
}
