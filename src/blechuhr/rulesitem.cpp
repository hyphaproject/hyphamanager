#include "rulesitem.h"
#include "ui_rulesitem.h"

RulesItem::RulesItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RulesItem)
{
    ui->setupUi(this);
}
RulesItem::RulesItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::RulesItem)
{
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->database = database;
    initType();
    init();
}

RulesItem::RulesItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::RTYPE type, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::RulesItem)
{
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

RulesItem::~RulesItem()
{
    delete ui;
}

void RulesItem::save()
{
    QSqlQuery query = database->getQuery();
    if(id.isEmpty()){
        query.prepare("insert into rules(username, type, start, end) values(:username, :type, :start, :end);");
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
    }else{
        query.prepare("update rules set username=:username, type=:type, start=:start, end=:end where id = :id;");
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
        query.bindValue(":id", this->id);
    }
    query.exec();
}

void RulesItem::deleteFromDatabase()
{
    QSqlQuery query = database->getQuery();
    if(id.isEmpty()){
    }else{
        query.prepare("delete from rules where id = :id;");
        query.bindValue(":id", this->id);
        query.exec();
    }
}

void RulesItem::init()
{
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::RTypeToString(type)));
}

void RulesItem::initType()
{
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
