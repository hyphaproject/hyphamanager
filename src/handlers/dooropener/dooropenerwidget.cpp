#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtWidgets/QInputDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "dooropenerwidget.h"
#include "ui_dooropenerwidget.h"

DoorOpenerWidget::DoorOpenerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoorOpenerWidget)
{
    ui->setupUi(this);
}

DoorOpenerWidget::~DoorOpenerWidget()
{
    delete ui;
}

void DoorOpenerWidget::setDatabase(Database *database)
{
    this->database = database;
}

void DoorOpenerWidget::setUserDatabase(UserDatabase *userDatabase)
{
    this->userDatabase = userDatabase;
}

void DoorOpenerWidget::setId(QString id)
{
    this->id = id;
}

void DoorOpenerWidget::loadConfig(QString json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if(object.contains("mastercard")){
        ui->masterCardEdit->setText(object.value("mastercard").toString());
    }
    if(object.contains("email")){
        ui->emailCheckBox->setChecked(object.value("email").toBool());
    }
    if(object.contains("fingerprint")){
        ui->fingerprintCheckBox->setChecked(object.value("fingerprint").toBool());
    }
    reloadUser();
}

void DoorOpenerWidget::reloadUser()
{
    listModel.clear();
    ui->listView->setModel(&listModel);
    QSqlQuery query = database->getQuery();
    query.exec("select user,atworktime from dooropener_user where id='"+ id +"'");
    while( query.next() ){
        QStandardItem* item = new QStandardItem(query.value(0).toString());
        item->setCheckable(true);
        item->setCheckState(query.value(1).toBool()?Qt::Checked:Qt::Unchecked);
        listModel.appendRow(item);
    }
}

QString DoorOpenerWidget::getConfig()
{
    return "{\"mastercard\":\""+ui->masterCardEdit->text()+"\""
            +",\"email\":"+(ui->emailCheckBox->isChecked()?QString("true"):QString("false"))
            +",\"fingerprint\":"+(ui->fingerprintCheckBox->isChecked()?QString("true"):QString("false"))+"}";
}

void DoorOpenerWidget::on_deleteButton_clicked()
{
    QString user = this->listModel.itemFromIndex(ui->listView->currentIndex())->text();
    QSqlQuery query = database->getQuery();
    query.prepare("DELETE FROM dooropener_user WHERE `id`='"+id+"' AND `user`='"+user+"';");
    qDebug() << user << id;
    query.exec();
    qDebug() << query.lastError().text();
    reloadUser();
}

void DoorOpenerWidget::on_addButton_clicked()
{
    bool ok;
    QString user = QInputDialog::getItem(this, tr("Add User"),
                                         tr("User:"), userDatabase->getUsers(), 0, false, &ok);
    if (ok && !user.isEmpty()){
        QSqlQuery query = database->getQuery();
        query.prepare("insert into dooropener_user(id,user,atworktime) values(:id, :user, :atworktime);");
        query.bindValue(":id",id);
        query.bindValue(":user",user);
        query.bindValue(":atworktime",false);
        query.exec();
        reloadUser();
    }
}
