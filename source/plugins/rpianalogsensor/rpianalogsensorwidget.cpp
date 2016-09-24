// Copyright (c) 2015-2016 Hypha
#include "rpianalogsensorwidget.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "ui_rpianalogsensorwidget.h"

RpiAnalogSensorWidget::RpiAnalogSensorWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RpiAnalogSensorWidget) {
  ui->setupUi(this);
}

RpiAnalogSensorWidget::~RpiAnalogSensorWidget() { delete ui; }

void RpiAnalogSensorWidget::setHost(QString host) { this->host = host; }

void RpiAnalogSensorWidget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("alarm")) {
    ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
  }
  if (object.contains("pin")) {
    ui->pinSpinBox->setValue(object.value("pin").toInt(0));
  }
  if (object.contains("min")) {
    ui->minSpinBox->setValue(object.value("min").toInt(0));
  }
  if (object.contains("max")) {
    ui->maxSpinBox->setValue(object.value("max").toInt(0));
  }
}

QString RpiAnalogSensorWidget::getConfig() {
  QJsonObject object;
  object["alarm"] = ui->alarmCheckBox->isChecked();
  object["pin"] = ui->pinSpinBox->value();
  object["min"] = ui->minSpinBox->value();
  object["max"] = ui->maxSpinBox->value();
  QJsonDocument document(object);
  return document.toJson(QJsonDocument::Compact);
}
