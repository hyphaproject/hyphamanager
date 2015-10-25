
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "serverstatuswidget.h"
#include "ui_serverstatuswidget.h"

ServerStatusWidget::ServerStatusWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ServerStatusWidget) {
  ui->setupUi(this);
}

ServerStatusWidget::~ServerStatusWidget() {
  delete ui;
}

void ServerStatusWidget::loadConfig(QString config) {
  QJsonDocument document = QJsonDocument::fromJson(config.toUtf8());
  QJsonObject object = document.object();
}

QString ServerStatusWidget::getConfig() {
  return "{}";
}
