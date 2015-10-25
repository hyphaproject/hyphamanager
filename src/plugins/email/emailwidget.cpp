#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "emailwidget.h"
#include "ui_emailwidget.h"

EMailWidget::EMailWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::EMailWidget) {
  ui->setupUi(this);
}

EMailWidget::~EMailWidget() {
  delete ui;
}

void EMailWidget::setHost(QString host) {
  this->host = host;
}

void EMailWidget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("user")) {
    ui->userEdit->setText(object.value("user").toString());
  }
  if (object.contains("password")) {
    ui->passwordEdit->setText(object.value("password").toString());
  }
  if (object.contains("host")) {
    ui->hostEdit->setText(object.value("host").toString());
  }
  if (object.contains("port")) {
    ui->portSpinBox->setValue(object.value("port").toInt(25));
  }
  if (object.contains("recipient")) {
    ui->recipientEdit->setText(object.value("recipient").toString());
  }
}

QString EMailWidget::getConfig() {
  return "{\"user\":\"" + ui->userEdit->text() + "\""
         + ",\"password\":\"" + ui->passwordEdit->text() + "\""
         + ",\"recipient\":\"" + ui->recipientEdit->text() + "\""
         + ",\"host\":\"" + ui->hostEdit->text() + "\""
         + ",\"port\":" + QString::number(ui->portSpinBox->value()) + "}";
}
