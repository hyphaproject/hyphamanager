// Copyright (c) 2015-2017 Hypha

#include "plugin/autopluginwidget.h"
#include "ui_autopluginwidget.h"

#include <limits>

#include <confdesc/confdesc.h>
#include <confdesc/datatypes.h>
#include <hypha/controller/plugin.h>

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

AutoPluginWidget::AutoPluginWidget(hypha::plugin::HyphaBasePlugin* plugin,
                                   hypha::database::Database* database,
                                   QWidget* parent)
    : QWidget(parent), ui(new Ui::AutoPluginWidget) {
  this->plugin = plugin;
  this->database = database;
  ui->setupUi(this);
  ui->nameLabel->setText(QString::fromStdString(plugin->getId()));
  ui->descriptionLabel->setText(
      QString::fromStdString(plugin->getDescription()));
  setupUi();
}

AutoPluginWidget::~AutoPluginWidget() { delete ui; }

void AutoPluginWidget::setupUi() {
  try {
    std::string description = plugin->getConfigDescription();
    cd::ConfDesc desc(description);
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;

      switch (item.getType()) {
        case cd::DataType::BOOLEAN: {
          QCheckBox* checkbox = new QCheckBox();
          checkbox->setChecked(item.getValue<bool>());
          checkbox->setText(QString::fromStdString(item.getDescription()) +
                            " ");
          addWidgets(checkbox);
          addItem(item.getName(), checkbox);
        } break;
        case cd::DataType::FLOAT: {
          QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
          doubleSpinBox->setValue(item.getValue<double>());
          doubleSpinBox->setPrefix(QString::fromStdString(item.getName()) +
                                   " ");
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     doubleSpinBox);
          addItem(item.getName(), doubleSpinBox);
        } break;
        case cd::DataType::INTEGER: {
          QSpinBox* spinBox = new QSpinBox();

          if (item.hasMax())
            spinBox->setMaximum(item.getMax());
          else
            spinBox->setMaximum(std::numeric_limits<int>::max());
          if (item.hasMin())
            spinBox->setMinimum(item.getMin());
          else
            spinBox->setMinimum(std::numeric_limits<int>::min());

          spinBox->setValue(item.getValue<int>());

          spinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     spinBox);
          addItem(item.getName(), spinBox);
        } break;
        case cd::DataType::STRING: {
          QLineEdit* lineEdit = new QLineEdit();

          if (item.hasMax())
            lineEdit->setMaxLength(item.getMax());
          else
            lineEdit->setMaxLength(std::numeric_limits<int>::max());

          lineEdit->setText(
              QString::fromStdString(item.getValue<std::string>()));

          lineEdit->setToolTip(QString::fromStdString(item.getName()));
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     lineEdit);
          addItem(item.getName(), lineEdit);
        } break;
        default:
          break;
      };
    }
  } catch (std::exception& e) {
    QLabel* label = new QLabel();
    label->setText(QString::fromStdString(e.what()));
    ui->layout->addWidget(label);
  }
}

void AutoPluginWidget::loadConfig(std::string json) {
  QJsonDocument document =
      QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
  QJsonObject object = document.object();

  try {
    cd::ConfDesc desc(plugin->getConfigDescription());
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;
      if (object.contains(QString::fromStdString(item.getName()))) {
        switch (item.getType()) {
          case cd::DataType::BOOLEAN: {
            QCheckBox* checkbox = (QCheckBox*)this->items[item.getName()];
            checkbox->setChecked(
                object.value(QString::fromStdString(item.getName())).toBool());
          } break;

          case cd::DataType::FLOAT: {
            QDoubleSpinBox* doubleSpinBox =
                (QDoubleSpinBox*)this->items[item.getName()];
            doubleSpinBox->setValue(
                object.value(QString::fromStdString(item.getName()))
                    .toDouble());

          } break;

          case cd::DataType::INTEGER: {
            QSpinBox* spinBox = (QSpinBox*)this->items[item.getName()];
            spinBox->setValue(
                object.value(QString::fromStdString(item.getName())).toInt());

          } break;

          case cd::DataType::STRING: {
            QLineEdit* lineEdit = (QLineEdit*)this->items[item.getName()];
            lineEdit->setText(
                object.value(QString::fromStdString(item.getName()))
                    .toString());
          } break;

          default:
            break;
        };
      }
    }
  } catch (std::exception& e) {
    QLabel* label = new QLabel();
    label->setText(QString::fromStdString(e.what()));
    ui->layout->addWidget(label);
  }
}

std::string AutoPluginWidget::getConfig() {
  QJsonObject object;

  try {
    cd::ConfDesc desc(plugin->getConfigDescription());
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;
      switch (item.getType()) {
        case cd::DataType::BOOLEAN: {
          QCheckBox* checkbox = (QCheckBox*)this->items[item.getName()];
          object[QString::fromStdString(item.getName())] =
              checkbox->isChecked();
        } break;

        case cd::DataType::FLOAT: {
          QDoubleSpinBox* doubleSpinBox =
              (QDoubleSpinBox*)this->items[item.getName()];
          object[QString::fromStdString(item.getName())] =
              doubleSpinBox->value();
        } break;

        case cd::DataType::INTEGER: {
          QSpinBox* spinBox = (QSpinBox*)this->items[item.getName()];
          object[QString::fromStdString(item.getName())] = spinBox->value();
        } break;

        case cd::DataType::STRING: {
          QLineEdit* lineEdit = (QLineEdit*)this->items[item.getName()];
          object[QString::fromStdString(item.getName())] = lineEdit->text();
        } break;

        default:
          break;
      };
    }
  } catch (std::exception& e) {
    QLabel* label = new QLabel();
    label->setText(QString::fromStdString(e.what()));
    ui->layout->addWidget(label);
  }

  QJsonDocument document(object);
  std::string json =
      QString(document.toJson(QJsonDocument::Compact)).toStdString();
  return json;
}

void AutoPluginWidget::addWidgets(QWidget* widget1, QWidget* widget2) {
  QHBoxLayout* hLayout = new QHBoxLayout();
  hLayout->addWidget(widget1);

  if (widget2) hLayout->addWidget(widget2);
  QWidget* w = new QWidget();
  w->setLayout(hLayout);
  ui->layout->addWidget(w);
}

void AutoPluginWidget::addItem(std::string name, QWidget* widget) {
  this->items.insert(std::pair<std::string, QWidget*>(name, widget));
  widget->setObjectName(QString::fromStdString(name));
}

void AutoPluginWidget::on_saveButton_clicked() {
  hypha::controller::Plugin plugin(this->database);
  plugin.updateConfig(this->plugin->getId(), getConfig());
}
