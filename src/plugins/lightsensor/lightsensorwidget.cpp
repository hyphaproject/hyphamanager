#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "lightsensorwidget.h"
#include "ui_lightsensorwidget.h"

LightSensorWidget::LightSensorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightSensorWidget)
{
    ui->setupUi(this);
}

LightSensorWidget::~LightSensorWidget()
{
    delete ui;
}

void LightSensorWidget::setHost(QString host)
{
    this->host = host;
}

void LightSensorWidget::loadConfig(QString json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if(object.contains("alarm")){
        ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
    }
}

QString LightSensorWidget::getConfig()
{
    QJsonObject object;
    object["alarm"] = ui->alarmCheckBox->isChecked();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}
