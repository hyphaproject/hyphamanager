#include "workingtimeprinter.h"
#include "workingtimealgo.h"
#include "model/rules/rulesfactory.h"
#include <algorithm>
#include <QObject>

WorkingTimePrinter::WorkingTimePrinter(QPrinter * printer)
{
    this->printer = printer;
    width = printer->width();
    height = printer->height();
}

WorkingTimePrinter::~WorkingTimePrinter()
{

}

void WorkingTimePrinter::setUsername(QString username)
{
    this->username = username;
}

/**
 * @brief WorkingTimePrinter::setName
 * @param name
 * set the full name of the username
 */
void WorkingTimePrinter::setName(QString name)
{
    this->name = name;
}

void WorkingTimePrinter::setMonth(QDate month)
{
    this->month = month;
}

void WorkingTimePrinter::setAccounts(QList<BaseAccount *> accounts)
{
    this->accounts = accounts;
}

void WorkingTimePrinter::setRules(QList<QString> rules)
{
    this->rules = rules;
}

void WorkingTimePrinter::setWorkingTimes(QList<WorkingTime *> times)
{
    this->times = times;
}

void WorkingTimePrinter::print()
{
    calculate();
    painter.begin(printer);
    printHeader();
    printDates();
    printTimes();
    printSum();
    printType();
    printFooter();
    painter.end();
}

void WorkingTimePrinter::calculate()
{
    std::sort(times.begin(), times.end(), WorkingTime::before);
    BaseRule * rule = 0;
    for(QString type: rules){
        if(rule){
            rule = RulesFactory::getRule(type, rule->getAccounts(), rule->getWorkingTimes());
        }else{
            rule = RulesFactory::getRule(type, accounts, times);
        }
        rule->calculate();
    }
    if(rule){
        this->accounts = rule->getAccounts();
        this->times = rule->getWorkingTimes();
    }
    std::sort(times.begin(), times.end(), WorkingTime::before);
}

/**
 * @brief WorkingTimePrinter::getHeight
 * @param h
 * @return
 * returns height calculated to a printer height as 1000.
 */
float WorkingTimePrinter::relHeight(int h)
{
    return h * height / 1000;
}

float WorkingTimePrinter::relWidth(int w)
{
    return w * width / 1000;
}

/**
 * @brief WorkingTimePrinter::printHeader
 * prints the header with username, name and date
 */
void WorkingTimePrinter::printHeader()
{
    QRect rect(0,0,width, relHeight(100));
    painter.drawRect(rect);
    painter.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, username);
    painter.drawText(rect, Qt::AlignRight | Qt::TextWordWrap, month.toString("MMMM yyyy"));

    rect = QRect(relWidth(50), relHeight(50), relWidth(100), relHeight(25));
    painter.drawText(rect, Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap, "Date");
    rect = QRect(relWidth(150), relHeight(50), relWidth(200), relHeight(25));
    painter.drawText(rect, Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap, "From\tTo");
    rect = QRect(relWidth(350), relHeight(50), relWidth(50), relHeight(25));
    painter.drawText(rect, Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap, ""+QString(QChar(0x2211)));
    rect = QRect(relWidth(400), relHeight(50), relWidth(50), relHeight(25));
    painter.drawText(rect, Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap, "Type");
}

void WorkingTimePrinter::printDates()
{
    int y = relHeight(100);
    int rowHeight = relHeight(25);
    foreach(WorkingTime *wt, times){
        QRect rect(relWidth(50), y, relWidth(100), rowHeight);
        painter.drawRect(rect);
        QString text = wt->getStart().toLocalTime().toString("ddd dd.");
        painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, text);
        y += rowHeight;
    }
}

void WorkingTimePrinter::printTimes()
{
    int y = relHeight(100);
    int rowHeight = relHeight(25);
    foreach(WorkingTime *wt, times){
        QRect rect(relWidth(150), y, relWidth(200), rowHeight);
        painter.drawRect(rect);
        QString text = wt->getStart().toLocalTime().toString("hh:mm") + "\t-\t" + wt->getEnd().toLocalTime().toString("hh:mm");
        painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, text);
        y += rowHeight;
    }
}

void WorkingTimePrinter::printSum()
{
    int y = relHeight(100);
    int rowHeight = relHeight(25);
    foreach(WorkingTime *wt, times){
        QRect rect(relWidth(350), y, relWidth(50), rowHeight);
        painter.drawRect(rect);
        QString text = QString::number(wt->hours(), 'g', 2)+" h";
        painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, text);
        y += rowHeight;
    }
}

void WorkingTimePrinter::printType()
{
    int y = relHeight(100);
    int rowHeight = relHeight(25);
    foreach(WorkingTime *wt, times){
        QRect rect(relWidth(400), y, relWidth(50), rowHeight);
        painter.drawRect(rect);
        QString text = wt->getType();
        painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, text);
        y += rowHeight;
    }
}

void WorkingTimePrinter::printFooter()
{
    QRect rect(0, relHeight(900), width, relHeight(80));
    painter.drawRect(rect);
    painter.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, QObject::trUtf8("Hours worked this Month: "));
    painter.drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, QString::number(WorkingTimeAlgo::getHours(times)));
}

