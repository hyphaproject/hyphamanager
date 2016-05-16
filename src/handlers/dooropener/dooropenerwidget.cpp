#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtWidgets/QInputDialog>
#include <Poco/Data/RecordSet.h>
#include <QDebug>
#include "dooropenerwidget.h"
#include "ui_dooropenerwidget.h"

DoorOpenerWidget::DoorOpenerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoorOpenerWidget) {
    ui->setupUi(this);
}

DoorOpenerWidget::~DoorOpenerWidget() {
    delete ui;
}

void DoorOpenerWidget::setDatabase(hypha::database::Database *database) {
    this->database = database;
}

void DoorOpenerWidget::setUserDatabase(hypha::database::UserDatabase *userDatabase) {
    this->userDatabase = userDatabase;
}

void DoorOpenerWidget::setId(QString id) {
    this->id = id;
}

void DoorOpenerWidget::loadConfig(QString json) {
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if (object.contains("mastercard")) {
        ui->masterCardEdit->setText(object.value("mastercard").toString());
    }
    if (object.contains("email")) {
        ui->emailCheckBox->setChecked(object.value("email").toBool());
    }
    if (object.contains("fingerprint")) {
        ui->fingerprintCheckBox->setChecked(object.value("fingerprint").toBool());
    }
    reloadUser();
}

void DoorOpenerWidget::reloadUser() {
    listModel.clear();
    ui->listView->setModel(&listModel);

    Poco::Data::Statement statement = database->getStatement();
    statement << "select user,atworktime from dooropener_user where id='" + id.toStdString() + "'";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
        std::string user = rs[0].convert<std::string>();
        bool atworktime = rs[1].convert<bool>();
        QStandardItem *item = new QStandardItem(QString::fromStdString(user));
        item->setCheckable(true);
        item->setCheckState(atworktime ? Qt::Checked : Qt::Unchecked);
        listModel.appendRow(item);
    }
}

QString DoorOpenerWidget::getConfig() {
    return "{\"mastercard\":\"" + ui->masterCardEdit->text() + "\""
           + ",\"email\":" + (ui->emailCheckBox->isChecked() ? QString("true") : QString("false"))
           + ",\"fingerprint\":" + (ui->fingerprintCheckBox->isChecked() ? QString("true") : QString("false")) + "}";
}

void DoorOpenerWidget::on_deleteButton_clicked() {
    QString user = this->listModel.itemFromIndex(ui->listView->currentIndex())->text();

    Poco::Data::Statement statement = database->getStatement();
    statement << "DELETE FROM dooropener_user WHERE `id`='" + id.toStdString() + "' AND `user`='" + user.toStdString() + "';";
    statement.execute();

    reloadUser();
}

void DoorOpenerWidget::on_addButton_clicked() {
    QStringList users;
    for (std::string user : userDatabase->getUsers())
        users.append(QString::fromStdString(user));
    bool ok;
    QString user = QInputDialog::getItem(this, tr("Add User"),
                                         tr("User:"), users, 0, false, &ok);
    if (ok && !user.isEmpty()) {
        std::string idStr = id.toStdString();
        std::string userStr = user.toStdString();
        bool atworktime = false;
        Poco::Data::Statement statement = database->getStatement();
        statement << "insert into dooropener_user(id,user,atworktime) values(?, ?, ?);",
                  Poco::Data::Keywords::use(idStr), Poco::Data::Keywords::use(userStr), Poco::Data::Keywords::use(atworktime);
        statement.execute();
        reloadUser();
    }
}
