// Copyright (c) 2015-2016 Hypha
#include "hyphamanager/hmhandler/autohandlerwidget.h"
#include "ui_autohandlerwidget.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include <confdesc/confdesc.h>
#include <confdesc/datatypes.h>

AutoHandlerWidget::AutoHandlerWidget(hypha::handler::HyphaHandler* handler,
                                     QWidget* parent)
    : QWidget(parent), ui(new Ui::AutoHandlerWidget) {
  this->handler = handler;
  ui->setupUi(this);
  setupUi();
}

AutoHandlerWidget::~AutoHandlerWidget() { delete ui; }

void AutoHandlerWidget::setupUi() {
  try {
    cd::ConfDesc desc(handler->getConfigDescription());
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;

      switch (item.getType()) {
        case cd::DataType::BOOLEAN: {
          QCheckBox* checkbox = new QCheckBox();
          checkbox->setChecked(item.getValue<bool>());
          checkbox->setText(QString::fromStdString(item.getDescription()) +
                            " ");
          ui->layout->addWidget(checkbox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), checkbox));
        } break;
        case cd::DataType::FLOAT: {
          QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
          doubleSpinBox->setValue(item.getValue<double>());
          doubleSpinBox->setPrefix(QString::fromStdString(item.getName()) +
                                   " ");
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     doubleSpinBox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), doubleSpinBox));
        } break;
        case cd::DataType::INTEGER: {
          QSpinBox* spinBox = new QSpinBox();
          spinBox->setValue(item.getValue<int>());
          spinBox->setMaximum(item.getMax());
          spinBox->setMinimum(item.getMin());
          spinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     spinBox);
          this->items.insert(
              std::pair<std::string, QWidget*>(item.getName(), spinBox));
        } break;
        case cd::DataType::STRING: {
          QLineEdit* lineEdit = new QLineEdit();
          lineEdit->setText(
              QString::fromStdString(item.getValue<std::string>()));
          lineEdit->setMaxLength(item.getMax());
          lineEdit->setToolTip(QString::fromStdString(item.getName()));
          addWidgets(new QLabel(QString::fromStdString(item.getDescription())),
                     lineEdit);
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

void AutoHandlerWidget::loadConfig(std::string json) {
  QJsonDocument document =
      QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
  QJsonObject object = document.object();

  try {
    cd::ConfDesc desc(handler->getConfigDescription());
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

std::string AutoHandlerWidget::getConfig() {
  QJsonObject object;

  try {
    cd::ConfDesc desc(handler->getConfigDescription());
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
  return QString(document.toJson(QJsonDocument::Compact)).toStdString();
}

void AutoHandlerWidget::addWidgets(QWidget* widget1, QWidget* widget2) {
  QHBoxLayout* hLayout = new QHBoxLayout();
  hLayout->addWidget(widget1);

  if (widget2) hLayout->addWidget(widget2);
  QWidget* w = new QWidget();
  w->setLayout(hLayout);
  ui->layout->addWidget(w);
}
