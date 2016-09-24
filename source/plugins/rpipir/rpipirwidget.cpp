// Copyright (c) 2015-2016 Hypha
#include "rpipirwidget.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "ui_rpipirwidget.h"

RpiPirWidget::RpiPirWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RpiPirWidget) {
  ui->setupUi(this);
}

RpiPirWidget::~RpiPirWidget() { delete ui; }

void RpiPirWidget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("log")) {
    ui->logCheckBox->setChecked(object.value("log").toBool(false));
  }
  if (object.contains("alarm")) {
    ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
  }
  if (object.contains("pin")) {
    ui->pinSpinBox->setValue(object.value("pin").toInt(29));
  }
}

QString RpiPirWidget::getConfig() {
  QJsonObject object;
  object["alarm"] = ui->alarmCheckBox->isChecked();
  object["log"] = ui->logCheckBox->isChecked();
  object["pin"] = ui->pinSpinBox->value();
  QJsonDocument document(object);
  return document.toJson();
}
