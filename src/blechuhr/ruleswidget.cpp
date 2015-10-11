#include <QtCore/QDate>
#include "ruleswidget.h"
#include "rulesadddialog.h"
#include "rulesitem.h"
#include "ui_ruleswidget.h"

RulesWidget::RulesWidget(QString username, Database *database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RulesWidget)
{
    ui->setupUi(this);
    this->username = username;
    this->database = database;
    init();
}

RulesWidget::~RulesWidget()
{
    delete ui;
}

void RulesWidget::init()
{
    loadRules();
}

void RulesWidget::loadRules()
{
    ui->listWidget->clear();
    QString queryString = "SELECT id, start, end, type FROM rules WHERE username = '" + this->username + "' ORDER BY start DESC;";
    QSqlQuery query = database->getQuery();
    query.exec(queryString);
    while( query.next() ){
        QString id = query.value(0).toString();
        QDateTime start = query.value(1).toDateTime();
        start.setTimeSpec(Qt::UTC);
        QDateTime end = query.value(2).toDateTime();
        end.setTimeSpec(Qt::UTC);
        QString type = query.value(3).toString();
        hypha::blechuhr::RTYPE t = hypha::blechuhr::StringToRType(type.toStdString());
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        RulesItem *rulesItem = new RulesItem(id, username, start, end, t, database);
        item->setSizeHint(rulesItem->minimumSizeHint());
        ui->listWidget->setItemWidget(item, rulesItem);
    }
}

void RulesWidget::on_addButton_clicked()
{
    RulesAddDialog rAddDialog(this->username, QDate::currentDate(), database);
    rAddDialog.exec();
    init();
}

void RulesWidget::on_deleteButton_clicked()
{
    RulesItem *item = (RulesItem*) ui->listWidget->itemWidget(ui->listWidget->currentItem());
    if(item){
        item->deleteFromDatabase();
        init();
    }
}

void RulesWidget::on_saveButton_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        RulesItem * item = (RulesItem*) ui->listWidget->itemWidget(ui->listWidget->item(i));
        item->save();
    }
    init();
}
