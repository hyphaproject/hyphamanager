#include <hypha/database/database.h>
#include "rulesitem.h"
#include "ui_rulesitem.h"

RulesItem::RulesItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RulesItem) {
    ui->setupUi(this);
}
RulesItem::RulesItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::RulesItem) {
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->database = database;
    initType();
    init();
}

RulesItem::RulesItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::RulesItem) {
    ui->setupUi(this);
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->database = database;
    initType();
    init();
}

RulesItem::~RulesItem() {
    delete ui;
}

void RulesItem::save() {
    Poco::Data::Statement statement = database->getStatement();
    if(id.isEmpty()) {
        statement << "insert into rules(username, type, start, end) values(?, ?, ?, ?);",
                  Poco::Data::use(username.toStdString()),
                  Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                  Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString());
    } else {
        statement << "insert into rules(username, type, start, end) values(?, ?, ?, ?);",
                  Poco::Data::use(username.toStdString()),
                  Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                  Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(id.toStdString());
    }
    statement.execute();
}

void RulesItem::deleteFromDatabase() {
    if(id.isEmpty()) {
    } else {
        Poco::Data::Statement statement = database->getStatement();
        statement << "delete from rules where id = ?;",
                  Poco::Data::use(this->id.toStdString());
        statement.execute();
    }
}

void RulesItem::init() {
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::RTypeToString(type)));
}

void RulesItem::initType() {
    ui->typeComboBox->clear();
    int i = 0;
    for(const auto& t : hypha::blechuhr::RTYPE()) {
        QString type = QString::fromStdString(hypha::blechuhr::RTypeToString(t));
        ui->typeComboBox->addItem(type);
        ui->typeComboBox->setItemText(i, type);
        ui->typeComboBox->setItemIcon(i, QIcon(":/blechuhr/"+type));
        i++;
    }
}
