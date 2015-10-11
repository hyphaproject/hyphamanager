#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "watersensorwidget.h"
#include "ui_watersensorwidget.h"

WaterSensorWidget::WaterSensorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaterSensorWidget)
{
    ui->setupUi(this);
}

WaterSensorWidget::~WaterSensorWidget()
{
    delete ui;
}

void WaterSensorWidget::setHost(QString host)
{
    this->host = host;
}

void WaterSensorWidget::loadConfig(QString json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if(object.contains("alarm")){
        ui->alarmCheckBox->setChecked(object.value("alarm").toBool());
    }
    if(object.contains("pin")){
        ui->pinSpinBox->setValue(object.value("pin").toInt(6));
    }
}

QString WaterSensorWidget::getConfig()
{
    QJsonObject object;
    object["alarm"] = ui->alarmCheckBox->isChecked();
    object["pin"] = ui->pinSpinBox->value();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}
