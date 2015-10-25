#include <QtCore/QDate>
#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include "ruleswidget.h"
#include "rulesadddialog.h"
#include "rulesitem.h"
#include "ui_ruleswidget.h"

RulesWidget::RulesWidget(QString username, hypha::database::Database *database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RulesWidget) {
    ui->setupUi(this);
    this->username = username;
    this->database = database;
    init();
}

RulesWidget::~RulesWidget() {
    delete ui;
}

void RulesWidget::init() {
    loadRules();
}

void RulesWidget::loadRules() {
    ui->listWidget->clear();

    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT id, start, end, type FROM rules WHERE username = '" + this->username.toStdString() + "' ORDER BY start DESC;";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        std::string id = rs[0].convert<std::string>();
        std::string starttime = rs[1].convert<std::string>();
        QDateTime startdatetime = QDateTime::fromString(QString::fromStdString(starttime));
        std::string endtime = rs[2].convert<std::string>();
        QDateTime enddatetime = QDateTime::fromString(QString::fromStdString(endtime));
        std::string type = rs[3].convert<std::string>();
        startdatetime.setTimeSpec(Qt::UTC);
        enddatetime.setTimeSpec(Qt::UTC);
        hypha::blechuhr::RTYPE t = hypha::blechuhr::StringToRType(type);
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        RulesItem *rulesItem = new RulesItem(QString::fromStdString(id), username, startdatetime, enddatetime, t, database);
        item->setSizeHint(rulesItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, rulesItem);
    }
}

void RulesWidget::on_addButton_clicked() {
    RulesAddDialog rAddDialog(this->username, QDate::currentDate(), database);
    rAddDialog.exec();
    init();
}

void RulesWidget::on_deleteButton_clicked() {
    RulesItem *item = (RulesItem*) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if(item) {
        item->deleteFromDatabase();
        init();
    }
}

void RulesWidget::on_saveButton_clicked() {
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        RulesItem * item = (RulesItem*) ui->listWidget->itemWidget(ui->listWidget->item(i));
        item->save();
    }
    init();
}
