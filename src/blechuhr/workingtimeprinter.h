#ifndef WORKINGTIMEPRINTER_H
#define WORKINGTIMEPRINTER_H

#include <QtPrintSupport/QPrinter>
#include <QtGui/QPainter>
#include <QtCore/QDate>

#include "model/workingtime.h"
#include "model/baseaccount.h"
#include "model/rules/baserule.h"

class WorkingTimePrinter {
  public:
    WorkingTimePrinter(QPrinter *printer);
    ~WorkingTimePrinter();

    void setUsername(QString username);
    void setName(QString name);
    void setMonth(QDate month);
    void setAccounts(QList<BaseAccount *> accounts);
    void setRules(QList<QString> rules);
    void setWorkingTimes(QList<WorkingTime *> times);
    void print();
    void calculate();

  protected:
    QPrinter *printer;
    QString username;
    QString name;
    QDate month;
    QPainter painter;
    int width;
    int height;
    QList<WorkingTime *> times;
    QList<BaseAccount *> accounts;
    QList<QString> rules;

    //
    float relHeight(int h);
    float relWidth(int w);
    void printHeader();
    void printDates();
    void printTimes();
    void printSum();
    void printType();
    void printFooter();

};

#endif // WORKINGTIMEPRINTER_H
