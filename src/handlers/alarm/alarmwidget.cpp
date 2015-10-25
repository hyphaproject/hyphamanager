
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AlarmWidget) {
  ui->setupUi(this);
}

AlarmWidget::~AlarmWidget() {
  delete ui;
}

void AlarmWidget::loadConfig(QString config) {
  QJsonDocument document = QJsonDocument::fromJson(config.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("savedir")) {
  }

}

QString AlarmWidget::getConfig() {
  return "{\"savedir\":\"\"}";
}
