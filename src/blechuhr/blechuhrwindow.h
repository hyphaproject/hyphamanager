#ifndef BLECHUHRWINDOW_H
#define BLECHUHRWINDOW_H

#include <QtWidgets/QWidget>
#include "../main/instance.h"
#include "../database/database.h"
#include "summarywidget.h"
#include "accountwidget.h"
#include "ruleswidget.h"
#include "exportwidget.h"


namespace Ui {
class BlechuhrWindow;
}

class BlechuhrWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BlechuhrWindow(Instance * instance, QWidget *parent = 0);
    ~BlechuhrWindow();

public slots:
    void reload();
    void reloadTab(int index);
    void reloadAccounts();
    void reloadRules();
    void reloadDay();
    void reloadMonth();
    void reloadSummary();
    void reloadExport();

private:
    Ui::BlechuhrWindow *ui;

protected:
    Instance * instance;
    SummaryWidget * summaryWidget;
    AccountWidget * accountWidget;
    RulesWidget * rulesWidget;
    ExportWidget * exportWidget;
private slots:
    void initDayWebView();
    void initMonthWebView();
    void on_userList_currentTextChanged(const QString &currentText);
    void addDayRows();
    void addDayWorkingTime();
    void addMonthRows();
    void updateDaySummary();
    void updateMonthSummary();

    void on_dayCalendarWidget_selectionChanged();
    void on_monthCalendarWidget_selectionChanged();
    void on_dayDataAddButton_clicked();
    void on_dayDataSaveButton_clicked();
    void on_exportButton_clicked();
    void on_importButton_clicked();
    void on_printToPDFButton_clicked();
    void on_importBlechuhrButton_clicked();
    void on_dayDataDeleteButton_clicked();
    void on_tab_currentChanged(int index);
};

#endif // BLECHUHRWINDOW_H
