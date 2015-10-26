#include <QtWebKitWidgets/QWebFrame>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QTemporaryFile>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/settings/hyphasettings.h>
#include <hypha/utils/email.h>
#include "deviceonlineimportdialog.h"
#include "deviceonlineimport.h"
#include "model/workingtime.h"
#include "workingtimeitem.h"
#include "workingtimeimportexport.h"
#include "workingtimeprinter.h"

#include "ui_deviceonlineimportdialog.h"

DeviceOnlineImportDialog::DeviceOnlineImportDialog(hypha::settings::HyphaSettings *settings, hypha::database::Database *database, hypha::database::UserDatabase *userDatabase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceOnlineImportDialog) {
    this->settings = settings;
    this->username = username;
    this->database = database;
    this->userDatabase = userDatabase;
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    init();
}

DeviceOnlineImportDialog::~DeviceOnlineImportDialog() {
    delete ui;
}

void DeviceOnlineImportDialog::on_DeviceOnlineImportDialog_accepted() {

}

void DeviceOnlineImportDialog::reload() {
    ui->webView->page()->mainFrame()->evaluateJavaScript("setUsername('" + ui->usernameComboBox->currentText() + "')");
    ui->webView->page()->mainFrame()->evaluateJavaScript("newTable()");

    DeviceOnlineImport deviceOnlineImport(database, userDatabase);
    deviceOnlineImport.setUsername(ui->usernameComboBox->currentText());
    deviceOnlineImport.setDate(ui->dateEdit->date());
    times.clear();
    for (WorkingTime wt : deviceOnlineImport.getMonth()) {
        times.append(new WorkingTime(wt));
        ui->webView->page()->mainFrame()->evaluateJavaScript(wt.toAddString(true));
    }
    ui->webView->page()->mainFrame()->evaluateJavaScript("drawChart()");

    reloadTimesList();
}

void DeviceOnlineImportDialog::reloadTimesList() {
    ui->timesListWidget->clear();
    for (WorkingTime *wt : times) {
        QListWidgetItem *item = new QListWidgetItem(ui->timesListWidget);
        ui->timesListWidget->addItem(item);
        WorkingTimeItem *workingTimeItem = new WorkingTimeItem(wt->getUsername(), wt->getStart(), wt->getEnd(), wt->getType(), database);
        item->setSizeHint(workingTimeItem->minimumSizeHint());
        ui->timesListWidget->setItemWidget(item, workingTimeItem);
    }
}

void DeviceOnlineImportDialog::init() {
    ui->usernameComboBox->clear();
    for (std::string username : userDatabase->getUsers()) {
        ui->usernameComboBox->addItem(QString::fromStdString(username));
    }

    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    ui->webView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->webView->load(QUrl("qrc:/blechuhr/html/blechuhr/day.html"));
}

void DeviceOnlineImportDialog::on_dateEdit_editingFinished() {
    reload();
}

void DeviceOnlineImportDialog::on_usernameComboBox_currentTextChanged(const QString &arg1) {
    reload();
}

void DeviceOnlineImportDialog::on_exportCSVButton_clicked() {
    if (ui->usernameComboBox->currentText() >= 0) {
        QFileDialog fileDialog(this);
        fileDialog.setNameFilter(tr("Comma Separated Values (*.csv *.txt *.dat)"));
        QStringList fileNames;
        if (fileDialog.exec())
            fileNames = fileDialog.selectedFiles();
        foreach(QString file, fileNames) {
            WorkingTimeImportExport importexport(ui->usernameComboBox->currentText(), times, file);
            importexport.exportData();
        }
    } else {
        QMessageBox::warning(this, "Export", "Please select a user to export data from.");
    }
}

void DeviceOnlineImportDialog::on_printPDFButton_clicked() {
    QFileDialog fileDialog(this);
    fileDialog.setNameFilter(tr("Portable Document Format (*.pdf)"));
    QStringList fileNames;
    if (fileDialog.exec())
        fileNames = fileDialog.selectedFiles();
    foreach(QString file, fileNames) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(file);
        WorkingTimePrinter timePrinter(&printer);
        timePrinter.setUsername(ui->usernameComboBox->currentText());
        timePrinter.setMonth(ui->dateEdit->date());
        timePrinter.setWorkingTimes(this->times);
        timePrinter.print();
        QApplication::restoreOverrideCursor();
    }
}

void DeviceOnlineImportDialog::on_mailPDFButton_clicked() {
    QTemporaryFile file(ui->usernameComboBox->currentText() + ui->dateEdit->date().toString("_MMM") + "_XXXXXX.pdf");
    if (file.open()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(file.fileName());
        WorkingTimePrinter timePrinter(&printer);
        timePrinter.setUsername(ui->usernameComboBox->currentText());
        timePrinter.setMonth(ui->dateEdit->date());
        timePrinter.setWorkingTimes(this->times);
        timePrinter.print();
        hypha::utils::EMail mail;
        mail.setHost(settings->getString("email.host", "localhost"));
        mail.setUser(settings->getString("email.user", ""));
        mail.setPassword(settings->getString("email.password", ""));
        mail.sendMessageWithAttachment(this->userDatabase->getMail(ui->usernameComboBox->currentText().toStdString()),
                                       "Time Record as PDF", "Here is your timerecord.\n Made with Hypha Manager ",
                                       (ui->dateEdit->date().toString("MMM") + ".pdf").toStdString(), file.fileName().toStdString() );
        QApplication::restoreOverrideCursor();
    }

}

void DeviceOnlineImportDialog::on_mailCSVButton_clicked() {
    QTemporaryFile file(ui->usernameComboBox->currentText() + ui->dateEdit->date().toString("_MMM") + "_XXXXXX.csv");
    if (file.open()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        WorkingTimeImportExport importexport(ui->usernameComboBox->currentText(), times, file.fileName());
        importexport.exportData();
        hypha::utils::EMail mail;
        mail.setHost(settings->getString("email.host", "localhost"));
        mail.setUser(settings->getString("email.user", ""));
        mail.setPassword(settings->getString("email.password", ""));
        mail.sendMessageWithAttachment(this->userDatabase->getMail(ui->usernameComboBox->currentText().toStdString()),
                                       "Time Record as CSV", "Here is your timerecord.\nPlease check it.\n Made with Hypha Manager ",
                                       (ui->dateEdit->date().toString("MMM") + ".pdf").toStdString(), file.fileName().toStdString() );
        QApplication::restoreOverrideCursor();
    }

}
