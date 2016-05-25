#include "autopluginwidget.h"
#include "ui_autopluginwidget.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include <confdesc/confdesc.h>
#include <confdesc/datatypes.h>

AutoPluginWidget::AutoPluginWidget(hypha::plugin::HyphaPlugin* plugin,
                                   QWidget* parent)
    : QWidget(parent), ui(new Ui::AutoPluginWidget) {
  this->plugin = plugin;
  ui->setupUi(this);
  setupUi();
}

AutoPluginWidget::~AutoPluginWidget() { delete ui; }

void AutoPluginWidget::setupUi() {
  try {
    cd::ConfDesc desc(plugin->getConfigDescription());
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;

      switch (item.getType()) {
        case cd::DataType::BOOLEAN: {
          QCheckBox* checkbox = new QCheckBox();
          checkbox->setChecked(item.getValue<bool>());
          checkbox->setText(QString::fromStdString(item.getName()) + " ");
          ui->layout->addWidget(checkbox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), checkbox));
        } break;
        case cd::DataType::FLOAT: {
          QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
          doubleSpinBox->setValue(item.getValue<double>());
          doubleSpinBox->setPrefix(QString::fromStdString(item.getName()) +
                                   " ");
          ui->layout->addWidget(doubleSpinBox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), doubleSpinBox));
        } break;
        case cd::DataType::INTEGER: {
          QSpinBox* spinBox = new QSpinBox();
          spinBox->setValue(item.getValue<int>());
          spinBox->setMaximum(item.getMax());
          spinBox->setMinimum(item.getMin());
          spinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
          ui->layout->addWidget(spinBox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), spinBox));
        } break;
        case cd::DataType::STRING: {
          QLineEdit* lineEdit = new QLineEdit();
          lineEdit->setText(
              QString::fromStdString(item.getValue<std::string>()));
          lineEdit->setMaxLength(item.getMax());
          lineEdit->setToolTip(QString::fromStdString(item.getName()));
          ui->layout->addWidget(lineEdit);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), lineEdit));
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
  std::string json = document.toJson(QJsonDocument::Compact).toStdString();
  return json;
}
