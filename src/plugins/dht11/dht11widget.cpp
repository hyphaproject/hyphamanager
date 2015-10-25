#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "dht11widget.h"
#include "ui_dht11widget.h"

Dht11Widget::Dht11Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Dht11Widget) {
  ui->setupUi(this);
}

Dht11Widget::~Dht11Widget() {
  delete ui;
}

void Dht11Widget::setHost(QString host) {
  this->host = host;
}

void Dht11Widget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("alarm")) {
    ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
  }
  if (object.contains("maxtemp")) {
    ui->maxTempSpinBox->setValue(object.value("maxtemp").toInt(30));
  }
  if (object.contains("mintemp")) {
    ui->minTempSpinBox->setValue(object.value("mintemp").toInt(10));
  }
}

QString Dht11Widget::getConfig() {

  QJsonObject object;
  object["alarm"] = ui->alarmCheckBox->isChecked();
  object["maxtemp"] = ui->maxTempSpinBox->value();
  object["mintemp"] = ui->minTempSpinBox->value();
  QJsonDocument document(object);
  return document.toJson(QJsonDocument::Compact);
}
