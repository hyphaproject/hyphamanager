
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "videocontrolwidget.h"
#include "ui_videocontrolwidget.h"

VideoControlWidget::VideoControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControlWidget) {
    ui->setupUi(this);
}

VideoControlWidget::~VideoControlWidget() {
    delete ui;
}

void VideoControlWidget::loadConfig(QString config) {
    QJsonDocument document = QJsonDocument::fromJson(config.toUtf8());
    QJsonObject object = document.object();
    if (object.contains("savedir")) {
        ui->saveDirEdit->setText(object.value("savedir").toString());
    }

}

QString VideoControlWidget::getConfig() {
    return "{\"savedir\":\"" + ui->saveDirEdit->text() + "\"}";
}
