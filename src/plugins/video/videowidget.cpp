#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWidget)
{
    ui->setupUi(this);
}

VideoWidget::~VideoWidget()
{
    delete ui;
}

void VideoWidget::setHost(QString host)
{
    this->host = host;
}

void VideoWidget::loadConfig(QString json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject object = document.object();
    if(object.contains("fps")){
        ui->framesSpinBox->setValue(object.value("fps").toInt(1));
    }
    if(object.contains("width")){
        ui->widthSpinBox->setValue(object.value("width").toInt(320));
    }
    if(object.contains("height")){
        ui->heightSpinBox->setValue(object.value("height").toInt(240));
    }
    if(object.contains("port")){
        ui->portSpinBox->setValue(object.value("port").toInt(240));
    }
    if(object.contains("findpersons")){
        ui->findPersonsCheckBox->setChecked(object.value("findpersons").toBool());
    }
    if(object.contains("user")){
        ui->userEdit->setText(object.value("user").toString(""));
    }
    if(object.contains("password")){
        ui->userEdit->setText(object.value("password").toString(""));
    }

    if(object.contains("devices")){
        QJsonArray devices = object.value("devices").toArray();
        QJsonObject video0 = devices.at(0).toObject();
        ui->video0DeviceEdit->setText(video0.value("device").toString());
        ui->video0UpsideDownCheckBox->setChecked(video0.value("upsidedown").toBool());
        QJsonObject video1 = devices.at(1).toObject();
        ui->video1DeviceEdit->setText(video1.value("device").toString());
        ui->video1UpsideDownCheckBox->setChecked(video1.value("upsidedown").toBool());
        QJsonObject video2 = devices.at(2).toObject();
        ui->video2DeviceEdit->setText(video2.value("device").toString());
        ui->video2UpsideDownCheckBox->setChecked(video2.value("upsidedown").toBool());
        QJsonObject video3 = devices.at(3).toObject();
        ui->video3DeviceEdit->setText(video3.value("device").toString());
        ui->video3UpsideDownCheckBox->setChecked(video3.value("upsidedown").toBool());
    }

    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    ui->webView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->webView->load(QUrl("http://"+host+":"+QString::number(ui->portSpinBox->value())));
    ui->urlLabel->setText("<a href=\"http://"+host+":"+QString::number(ui->portSpinBox->value())
                          +"\">Video Stream http://"+host+":"+QString::number(ui->portSpinBox->value())+"</a>");

}

QString VideoWidget::getConfig()
{
    QJsonObject video0;
    video0["device"] = ui->video0DeviceEdit->text();
    video0["upsidedown"] = ui->video0UpsideDownCheckBox->isChecked();
    QJsonObject video1;
    video1["device"] = ui->video1DeviceEdit->text();
    video1["upsidedown"] = ui->video1UpsideDownCheckBox->isChecked();
    QJsonObject video2;
    video2["device"] = ui->video2DeviceEdit->text();
    video2["upsidedown"] = ui->video2UpsideDownCheckBox->isChecked();
    QJsonObject video3;
    video3["device"] = ui->video3DeviceEdit->text();
    video3["upsidedown"] = ui->video3UpsideDownCheckBox->isChecked();
    QJsonArray devices;
    devices.append(video0);
    devices.append(video1);
    devices.append(video2);
    devices.append(video3);
    QJsonObject object;
    object["fps"]= ui->framesSpinBox->value();
    object["width"] = ui->widthSpinBox->value();
    object["height"] = ui->heightSpinBox->value();
    object["port"] = ui->portSpinBox->value();
    object["findpersons"] = ui->findPersonsCheckBox->isChecked();
    object["user"] = ui->userEdit->text();
    object["password"] = ui->passwordEdit->text();
    object["devices"] = devices;
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}
