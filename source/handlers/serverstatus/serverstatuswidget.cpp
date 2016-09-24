// Copyright (c) 2015-2016 Hypha
#include "serverstatuswidget.h"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "ui_serverstatuswidget.h"

ServerStatusWidget::ServerStatusWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerStatusWidget) {
  ui->setupUi(this);
}

ServerStatusWidget::~ServerStatusWidget() { delete ui; }

void ServerStatusWidget::loadConfig(QString config) {
  QJsonDocument document = QJsonDocument::fromJson(config.toUtf8());
  QJsonObject object = document.object();
}

QString ServerStatusWidget::getConfig() { return "{}"; }
