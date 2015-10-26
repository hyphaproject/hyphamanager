
#include <QtWidgets/QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtCore/QTemporaryDir>
#include <QtCore/QDebug>
#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/utils/email.h>
#include "deviceonlineimport.h"
#include "workingtimeimportexport.h"
#include "workingtimeprinter.h"
#include "exportwidget.h"
#include "workingtimealgo.h"
#include "ui_exportwidget.h"

ExportWidget::ExportWidget(Instance *instance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportWidget) {
    this->instance = instance;
    ui->setupUi(this);
    init();
}

ExportWidget::~ExportWidget() {
    delete ui;
}

void ExportWidget::init() {
    ui->listView->setModel(&listModel);
    ui->dateFromEdit->setDate(QDate::currentDate());
    ui->dateToEdit->setDate(QDate::currentDate().addMonths(1));
    loadUser();
}

void ExportWidget::loadUser() {
    for (std::string user : instance->getUserDatabase()->getUsers()) {
        QStandardItem *item = new QStandardItem(QString::fromStdString(user));
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        listModel.appendRow(item);
    }
}

QString ExportWidget::getSaveDir() {
    return QFileDialog::getExistingDirectory(this, tr("Save Directory"),
            "",
            QFileDialog::ShowDirsOnly
            | QFileDialog::DontResolveSymlinks);
}

QString ExportWidget::exportRFID_to_CSV(QString username, QDate month, QString folder) {
    QString file = folder + "/" + username + "_" + month.toString("MMM_yy") + ".csv";
    DeviceOnlineImport deviceOnlineImport(instance->getDatabase(), instance->getUserDatabase());
    deviceOnlineImport.setUsername(username);
    deviceOnlineImport.setDate(month);

    WorkingTimeImportExport importexport(username, deviceOnlineImport.getMonth(), file);
    importexport.exportData();
    return file;
}

QString ExportWidget::exportRFID_to_PDF(QString username, QDate month, QString folder) {
    QString file = folder + "/" + username + "_" + month.toString("MMM_yy") + ".pdf";
    DeviceOnlineImport deviceOnlineImport(instance->getDatabase(), instance->getUserDatabase());
    deviceOnlineImport.setUsername(username);
    deviceOnlineImport.setDate(month);

    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    WorkingTimePrinter timePrinter(&printer);
    timePrinter.setUsername(username);
    timePrinter.setMonth(month);
    timePrinter.setWorkingTimes(deviceOnlineImport.getMonth());
    timePrinter.print();
    return file;
}

QString ExportWidget::exportReport_to_PDF(QString username, QDate month, QString folder) {
    QString file = folder + "/" + username + "_" + month.toString("MMM_yy") + ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    WorkingTimePrinter timePrinter(&printer);
    timePrinter.setUsername(username);
    timePrinter.setMonth(month);

    WorkingTimeAlgo algo(instance->getDatabase(), instance->getUserDatabase());
    algo.setUsername(username);
    algo.setDate(month);

    QList<WorkingTime *> workingTimes;
    for (WorkingTime wt : algo.getMonth()) {
        workingTimes.append(new WorkingTime(wt));
    }
    timePrinter.setWorkingTimes(workingTimes);

    Poco::Data::Statement statement = instance->getDatabase()->getStatement();
    statement << "SELECT id, start, end, type FROM rules WHERE username = '" + username.toStdString() + "' ORDER BY start DESC;";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    QList<QString> rules;
    while (more) {
        std::string id = rs[0].convert<std::string>();
        std::string starttime = rs[1].convert<std::string>();
        QDateTime startdatetime = QDateTime::fromString(QString::fromStdString(starttime));
        std::string endtime = rs[2].convert<std::string>();
        QDateTime enddatetime = QDateTime::fromString(QString::fromStdString(endtime));
        std::string type = rs[3].convert<std::string>();
        startdatetime.setTimeSpec(Qt::UTC);
        enddatetime.setTimeSpec(Qt::UTC);
        rules.append(QString::fromStdString(type));
        more = rs.moveNext();
    }

    timePrinter.setRules(rules);
    timePrinter.print();
    return file;
}

void ExportWidget::on_allUserCheckBox_toggled(bool checked) {
    for (int i = 0; i < listModel.rowCount(); ++i) {
        QStandardItem *item = listModel.item(i);
        item->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }
}

void ExportWidget::on_dateFromEdit_userDateChanged(const QDate &date) {
    ui->dateToEdit->setDate(date.addMonths(1));
}

void ExportWidget::on_filesButton_clicked() {
    QString dir = getSaveDir();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int i = 0; i < listModel.rowCount(); ++i) {
        QStandardItem *item = listModel.item(i);
        if (item->checkState() == Qt::Checked) {
            if (ui->rfidToCsvCheckBox->isChecked()) {
                this->exportRFID_to_CSV(item->text(), ui->dateFromEdit->date(), dir);
            }
            if (ui->rfidToPdfCheckBox->isChecked()) {
                this->exportRFID_to_PDF(item->text(), ui->dateFromEdit->date(), dir);
            }
            if (ui->reportCheckBox->isChecked()) {
                this->exportReport_to_PDF(item->text(), ui->dateFromEdit->date(), dir);
            }
        }
    }
    QApplication::restoreOverrideCursor();
}

void ExportWidget::on_emailButton_clicked() {
    QTemporaryDir dir;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int i = 0; i < listModel.rowCount(); ++i) {
        QStandardItem *item = listModel.item(i);
        if (item->checkState() == Qt::Checked) {
            hypha::utils::EMail mail;
            mail.setHost(instance->getClientSettings()->getString("email.host", "localhost"));
            mail.setUser(instance->getClientSettings()->getString("email.user", ""));
            mail.setPassword(instance->getClientSettings()->getString("email.password", ""));
            qDebug() << "Send Mail to: " + QString::fromStdString(instance->getUserDatabase()->getMail(item->text().toStdString()));
            if (ui->rfidToCsvCheckBox->isChecked()) {
                QString f = this->exportRFID_to_CSV(item->text(), ui->dateFromEdit->date(), dir.path());
                mail.sendMessageWithAttachment(instance->getUserDatabase()->getMail(item->text().toStdString()),
                                               "Draft Time Record as CSV for " + ui->dateFromEdit->date().toString("MMMM").toStdString(), "Here is your timerecord.\n Made with Hypha Manager ",
                                               (ui->dateFromEdit->date().toString("MMMM") + ".csv").toStdString(), f.toStdString() );
            }
            if (ui->rfidToPdfCheckBox->isChecked()) {
                QString f = this->exportRFID_to_PDF(item->text(), ui->dateFromEdit->date(), dir.path());
                mail.sendMessageWithAttachment(instance->getUserDatabase()->getMail(item->text().toStdString()),
                                               "Draft Time Record as PDF for " + ui->dateFromEdit->date().toString("MMMM").toStdString(), "Here is your timerecord.\n Made with Hypha Manager ",
                                               (ui->dateFromEdit->date().toString("MMMM") + ".pdf").toStdString(), f.toStdString() );
            }
        }
    }
    QApplication::restoreOverrideCursor();
}
