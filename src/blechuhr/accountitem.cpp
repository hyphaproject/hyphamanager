#include "accountitem.h"
#include "ui_accountitem.h"
#include "model/type.h"

AccountItem::AccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);
    initType();
    init();
}

AccountItem::AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->amount = amount;
    this->name = name;
    this->database = database;
    this->isIterative = false;
    initType();
    init();
}

AccountItem::AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);
    ui->iterativeCheckBox->hide();
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->amount = amount;
    this->name = name;
    this->database = database;
    this->isIterative = false;
    initType();
    init();
}

AccountItem::AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->itype = type;
    this->database = database;
    this->isIterative = true;
    this->starttime = starttime;
    this->endtime = endtime;
    initType();
    init();
}

AccountItem::AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);
    ui->iterativeCheckBox->hide();
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->itype = type;
    this->database = database;
    this->isIterative = true;
    this->starttime = starttime;
    this->endtime = endtime;
    initType();
    init();
}

AccountItem::~AccountItem()
{
    delete ui;
}

void AccountItem::save()
{
    QSqlQuery query = database->getQuery();
    if(isIterative){
        if(id.isEmpty()){
            query.prepare("insert into iterativeaccount(username, type, start, end, starttime, endtime) values(:username, :type, :start, :end, :starttime, :endtime);");
        }else{
            query.prepare("update iterativeaccount set username=:username, type=:type, start=:start, end=:end, starttime=:starttime, endtime=:endtime where id = :id;");
        }
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
        query.bindValue(":id", this->id);
        query.bindValue(":starttime", ui->startTimeEdit->time());
        query.bindValue(":endtime", ui->endTimeEdit->time());
    }else{
        if(id.isEmpty()){
            query.prepare("insert into account(username, type, start, end, amount, name) values(:username, :type, :start, :end, :amount, :name);");
        }else{
            query.prepare("update account set username=:username, type=:type, start=:start, end=:end, amount=:amount, name=:name where id = :id;");
        }
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
        query.bindValue(":id", this->id);
        query.bindValue(":amount", ui->amountSpinBox->value());
        query.bindValue(":name", ui->nameLineEdit->text());
    }
    query.exec();
}

void AccountItem::deleteFromDatabase()
{
    QSqlQuery query = database->getQuery();
    if(id.isEmpty()){
    }else{
        if(isIterative){
            query.prepare("delete from iterativeaccount where id = :id;");
            query.bindValue(":id", this->id);
        }else{
            query.prepare("delete from account where id = :id;");
            query.bindValue(":id", this->id);
        }

        query.exec();
    }
}

void AccountItem::init()
{
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    if(isIterative){
        ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::ITypeToString(itype)));
        ui->startTimeEdit->setTime(this->starttime);
        ui->endTimeEdit->setTime(this->endtime);
    }else{
        ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::TypeToString(type)));
        ui->nameLineEdit->setText(name);
        ui->amountSpinBox->setValue(amount);
    }
    updateElements();

}

void AccountItem::initType()
{
    ui->typeComboBox->clear();
    int i = 0;
    if(isIterative){
        for(const auto& t : hypha::blechuhr::ITYPE()) {
            QString type = QString::fromStdString(hypha::blechuhr::ITypeToString(t));
            ui->typeComboBox->addItem(type);
            ui->typeComboBox->setItemText(i, type);
            ui->typeComboBox->setItemIcon(i, QIcon(":/blechuhr/"+type));
            i++;
        }
    }else{
        for(const auto& t : hypha::blechuhr::TYPE()) {
            QString type = QString::fromStdString(hypha::blechuhr::TypeToString(t));
            ui->typeComboBox->addItem(type);
            ui->typeComboBox->setItemText(i, type);
            ui->typeComboBox->setItemIcon(i, QIcon(":/blechuhr/"+type));
            i++;
        }
    }
}


void AccountItem::on_iterativeCheckBox_clicked(bool checked)
{
    isIterative = checked;
    updateElements();
}

void AccountItem::updateElements()
{
    if(isIterative){
        ui->amountSpinBox->hide();
        ui->nameLineEdit->hide();
        ui->startTimeEdit->show();
        ui->endTimeEdit->show();
    }else{
        ui->amountSpinBox->show();
        ui->nameLineEdit->show();
        ui->startTimeEdit->hide();
        ui->endTimeEdit->hide();
    }
    initType();
    ui->horizontalLayout->addStretch();
}
