#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "flamewidget.h"
#include "ui_flamewidget.h"

FlameWidget::FlameWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FlameWidget) {
  ui->setupUi(this);
}

FlameWidget::~FlameWidget() {
  delete ui;
}

void FlameWidget::setHost(QString host) {
  this->host = host;
}

void FlameWidget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("alarm")) {
    ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
  }
}

QString FlameWidget::getConfig() {
  QJsonObject object;
  object["alarm"] = ui->alarmCheckBox->isChecked();
  QJsonDocument document(object);
  return document.toJson(QJsonDocument::Compact);
}
