#include "autohandlerwidget.h"
#include "ui_autohandlerwidget.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>

#include <confdesc/datatypes.h>
#include <confdesc/confdesc.h>

AutoHandlerWidget::AutoHandlerWidget(hypha::handler::HyphaHandler *handler, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoHandlerWidget)
{
    this->handler = handler;
    ui->setupUi(this);
    setupUi();
}

AutoHandlerWidget::~AutoHandlerWidget()
{
    delete ui;
}

void AutoHandlerWidget::setupUi()
{
    try {
    cd::ConfDesc desc(handler->getConfigDescription());
    for (const auto& items : desc) {
      cd::ConfigItem item = items.second;

      switch (item.getType()) {
        case cd::DataType::BOOLEAN: {
          QCheckBox* checkbox = new QCheckBox();
          checkbox->setChecked(item.getValue<bool>());
          checkbox->setText(QString::fromStdString(item.getName()) + " ");
          ui->layout->addWidget(checkbox);
            this->items.insert(std::pair<std::string, QWidget*>(item.getName(), checkbox));
        } break;
        case cd::DataType::FLOAT: {
          QDoubleSpinBox* doubleSpinBox = new QDoubleSpinBox();
          doubleSpinBox->setValue(item.getValue<double>());
          doubleSpinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
          ui->layout->addWidget(doubleSpinBox);
          this->items.insert(std::pair<std::string, QWidget*>(item.getName(), doubleSpinBox));
        } break;
        case cd::DataType::INTEGER: {
          QSpinBox* spinBox = new QSpinBox();
          spinBox->setValue(item.getValue<int>());
          spinBox->setMaximum(item.getMax());
          spinBox->setMinimum(item.getMin());
          spinBox->setPrefix(QString::fromStdString(item.getName()) + " ");
          ui->layout->addWidget(spinBox);
          this->items.insert(std::pair<std::string, QWidget*>(item.getName(), spinBox));
        } break;
        case cd::DataType::STRING: {
          QLineEdit* lineEdit = new QLineEdit();
          lineEdit->setText(QString::fromStdString(item.getValue<std::string>()));
          lineEdit->setMaxLength(item.getMax());
          lineEdit->setToolTip(QString::fromStdString(item.getName()));
          ui->layout->addWidget(lineEdit);
          this->items.insert(std::pair<std::string, QWidget*>(item.getName(), lineEdit));
        } break;
        default:
          break;
      };
    }
    }catch(std::exception &e){

    }
}

void AutoHandlerWidget::loadConfig(std::string json)
{

}

std::string AutoHandlerWidget::getConfig()
{
    return "{}";
}
