#include <QtWebKitWidgets/QWebFrame>
#include <QtCore/QThread>
#include <QtCore/QDateTime>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtGui/QPainter>
#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include "blechuhrwindow.h"
#include "workingtimealgo.h"
#include "summarymonth.h"
#include "workingtimeitem.h"
#include "workingtimeadddialog.h"
#include "workingtimeimportexport.h"
#include "summarywidget.h"
#include "deviceonlineimportdialog.h"

#include "ui_blechuhrwindow.h"
#include <QDebug>


BlechuhrWindow::BlechuhrWindow(Instance *instance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlechuhrWindow) {
    summaryWidget = 0;
    accountWidget = 0;
    rulesWidget = 0;
    exportWidget = 0;
    this->instance = instance;
    ui->setupUi(this);
    initDayWebView();
    initMonthWebView();
    reload();
}

BlechuhrWindow::~BlechuhrWindow() {
    delete ui;
}

void BlechuhrWindow::reload() {
    ui->userList->clear();
    for(std::string user: instance->getUserDatabase()->getUsers()) {
        ui->userList->addItem(QString::fromStdString(user));
    }

}

void BlechuhrWindow::reloadTab(int index) {
    switch(index) {
    case 0:
        reloadAccounts();
        break;
    case 1:
        reloadRules();
        break;
    case 2:
        reloadDay();
        break;
    case 3:
        reloadMonth();
        break;
    case 4:
        reloadSummary();
        break;
    case 5:
        reloadExport();
        break;
    default:
        break;
    }
}

void BlechuhrWindow::reloadAccounts() {
    if(ui->userList->currentItem() == 0) return;
    if(accountWidget) {
        delete accountWidget;
        this->accountWidget = 0;
    }
    accountWidget = new AccountWidget(ui->userList->currentItem()->text(), instance->getDatabase(), this);
    ui->accountsLayout->addWidget(accountWidget);
}

void BlechuhrWindow::reloadRules() {
    if(ui->userList->currentItem() == 0) return;
    if(rulesWidget) {
        delete rulesWidget;
        this->rulesWidget = 0;
    }
    rulesWidget = new RulesWidget(ui->userList->currentItem()->text(), instance->getDatabase(), this);
    ui->rulesLayout->addWidget(rulesWidget);
}

void BlechuhrWindow::reloadDay() {
    if(ui->userList->currentItem() == 0) return;
    ui->dayWebView->page()->mainFrame()->evaluateJavaScript("setUsername('"+ui->userList->currentItem()->text()+"')");
    ui->dayWebView->page()->mainFrame()->evaluateJavaScript("newTable()");
    addDayRows();
    ui->dayWebView->page()->mainFrame()->evaluateJavaScript("drawChart()");
    addDayWorkingTime();

}

void BlechuhrWindow::reloadMonth() {
    if(ui->userList->currentItem() == 0) return;
    ui->monthWebView->page()->mainFrame()->evaluateJavaScript("setUsername('"+ui->userList->currentItem()->text()+"')");
    ui->monthWebView->page()->mainFrame()->evaluateJavaScript("newTable()");
    addMonthRows();
    ui->monthWebView->page()->mainFrame()->evaluateJavaScript("drawChart()");
    updateMonthSummary();

}

void BlechuhrWindow::reloadSummary() {
    if(ui->userList->currentItem() == 0) return;
    if(summaryWidget) {
        delete summaryWidget;
        this->summaryWidget = 0;
    }
    summaryWidget = new SummaryWidget(ui->userList->currentItem()->text(), instance->getDatabase(), instance->getUserDatabase(), this);
    ui->summaryGridLayout->addWidget(summaryWidget);
}

void BlechuhrWindow::reloadExport() {
    if(exportWidget) {
        delete exportWidget;
        this->exportWidget = 0;
    }
    exportWidget = new ExportWidget(this->instance, this);
    ui->exportLayout->addWidget(exportWidget);
}

void BlechuhrWindow::initDayWebView() {
    ui->dayWebView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->dayWebView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    ui->dayWebView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->dayWebView->load(QUrl("qrc:/blechuhr/html/blechuhr/day.html"));
}

void BlechuhrWindow::initMonthWebView() {
    ui->monthWebView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->monthWebView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->monthWebView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    ui->monthWebView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    ui->monthWebView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->monthWebView->load(QUrl("qrc:/blechuhr/html/blechuhr/day.html"));
}

void BlechuhrWindow::on_userList_currentTextChanged(const QString &currentText) {
    ui->groupBox->setTitle(currentText);
    this->reloadTab(ui->tab->currentIndex());

}

void BlechuhrWindow::addDayRows() {
    WorkingTimeAlgo workingTimeAlgo(instance->getDatabase(), instance->getUserDatabase());
    workingTimeAlgo.setUsername(ui->userList->currentItem()->text());
    workingTimeAlgo.setDate(ui->dayCalendarWidget->selectedDate());
    foreach(WorkingTime wt, workingTimeAlgo.getDay()) {
        ui->dayWebView->page()->mainFrame()->evaluateJavaScript(wt.toAddString());
    }
}

void BlechuhrWindow::addDayWorkingTime() {
    ui->dayListWidget->clear();

    Poco::Data::Statement statement = instance->getDatabase()->getStatement();
    statement << "SELECT id, start, end, type FROM workingtime WHERE username = '" + ui->userList->currentItem()->text().toStdString()
              + "' AND DATE(start) = '" + ui->dayCalendarWidget->selectedDate().toString("yyyy-MM-dd").toStdString() +"'";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        std::string id = rs[0].convert<std::string>();
        std::string start = rs[1].convert<std::string>();
        QDateTime startTime = QDateTime::fromString(QString::fromStdString(start));
        std::string end = rs[2].convert<std::string>();
        QDateTime endTime = QDateTime::fromString(QString::fromStdString(end));
        std::string type = rs[3].convert<std::string>();

        startTime.setTimeSpec(Qt::UTC);
        endTime.setTimeSpec(Qt::UTC);

        QListWidgetItem *item = new QListWidgetItem(ui->dayListWidget);
        ui->dayListWidget->addItem(item);
        WorkingTimeItem *workingTimeItem = new WorkingTimeItem(QString::fromStdString(id), ui->userList->currentItem()->text(), startTime,
                endTime, QString::fromStdString(type),instance->getDatabase());
        item->setSizeHint(workingTimeItem->minimumSizeHint());
        ui->dayListWidget->setItemWidget(item, workingTimeItem);

        more = rs.moveNext();
    }
}

void BlechuhrWindow::addMonthRows() {
    WorkingTimeAlgo workingTimeAlgo(instance->getDatabase(), instance->getUserDatabase());
    workingTimeAlgo.setUsername(ui->userList->currentItem()->text());
    workingTimeAlgo.setDate(ui->monthCalendarWidget->selectedDate());
    foreach(WorkingTime wt, workingTimeAlgo.getMonth()) {
        ui->monthWebView->page()->mainFrame()->evaluateJavaScript(wt.toAddString());
    }
}

void BlechuhrWindow::updateDaySummary() {

}

void BlechuhrWindow::updateMonthSummary() {
    SummaryMonth summary(instance->getDatabase(), instance->getUserDatabase());
    summary.setUsername(ui->userList->currentItem()->text());
    summary.setDate(ui->monthCalendarWidget->selectedDate());
    summary.calculate();
    ui->monthSummarylineEdit->setText(QString::number( summary.getWorkedHours(), 'f', 2 ));
}

void BlechuhrWindow::on_dayCalendarWidget_selectionChanged() {
    reloadDay();
}

void BlechuhrWindow::on_monthCalendarWidget_selectionChanged() {
    reloadMonth();
}

void BlechuhrWindow::on_dayDataAddButton_clicked() {
    if(ui->userList->currentRow() >= 0) {
        WorkingTimeAddDialog wtAddDialog(ui->userList->currentItem()->text(), ui->dayCalendarWidget->selectedDate(), instance->getDatabase(), this);
        wtAddDialog.exec();
    }
}

void BlechuhrWindow::on_dayDataSaveButton_clicked() {
    for(int i = 0; i < ui->dayListWidget->count(); ++i) {
        WorkingTimeItem * item = (WorkingTimeItem*) ui->dayListWidget->itemWidget(ui->dayListWidget->item(i));
        item->save();
    }
    reloadDay();
}

void BlechuhrWindow::on_exportButton_clicked() {
    if(ui->userList->currentRow() >= 0 && summaryWidget) {
        QFileDialog fileDialog(this);
        fileDialog.setNameFilter(tr("Comma Separated Values (*.csv *.txt *.dat)"));
        QStringList fileNames;
        if (fileDialog.exec())
            fileNames = fileDialog.selectedFiles();
        foreach(QString file, fileNames) {
            WorkingTimeImportExport importexport(instance->getDatabase(), ui->userList->currentItem()->text(), file);
            importexport.exportDataFromDatabase();
        }
    } else {
        QMessageBox::warning(this, "Export", "Please select a user to export data from.");
    }
}

void BlechuhrWindow::on_importButton_clicked() {
    if(ui->userList->currentRow() >= 0) {
        QFileDialog fileDialog(this);
        fileDialog.setNameFilter(tr("Comma Separated Values (*.csv *.txt *.dat)"));
        QStringList fileNames;
        if (fileDialog.exec())
            fileNames = fileDialog.selectedFiles();
        foreach(QString file, fileNames) {
            WorkingTimeImportExport importexport(instance->getDatabase(), ui->userList->currentItem()->text(), file);
            importexport.importData();
        }
    } else {
        QMessageBox::warning(this, "Export", "Please select a user to import data from.");
    }
}

void BlechuhrWindow::on_printToPDFButton_clicked() {
    if(ui->userList->currentRow() >= 0 && summaryWidget) {
        QFileDialog fileDialog(this);
        fileDialog.setNameFilter(tr("Portable Document Format (*.pdf)"));
        QStringList fileNames;
        if (fileDialog.exec())
            fileNames = fileDialog.selectedFiles();
        foreach(QString file, fileNames) {
            QApplication::setOverrideCursor(Qt::WaitCursor);
            QPrinter printer(QPrinter::ScreenResolution);
            printer.setPaperSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(file);
            QPainter qPainter(&printer);
            summaryWidget->render(&qPainter, QPoint(), QRegion(), DrawChildren);
            qPainter.end();
            QApplication::restoreOverrideCursor();
        }
    } else {
        QMessageBox::warning(this, "Export", "Please select a user to export data from.");
    }

}

void BlechuhrWindow::on_importBlechuhrButton_clicked() {
    DeviceOnlineImportDialog dialog(instance->getClientSettings(), instance->getDatabase(), instance->getUserDatabase(), this);
    dialog.exec();
}

void BlechuhrWindow::on_dayDataDeleteButton_clicked() {

    WorkingTimeItem *item = (WorkingTimeItem*) ui->dayListWidget->itemWidget(ui->dayListWidget->currentItem());
    if(item) {
        item->deleteFromDatabase();
        reloadDay();
    }
}

void BlechuhrWindow::on_tab_currentChanged(int index) {
    reloadTab(index);
}
