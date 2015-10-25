#ifndef WORKINGTIMEITEM_H
#define WORKINGTIMEITEM_H

#include <QtWidgets/QWidget>
#include <QtCore/QDateTime>

namespace hypha {
namespace database {
    class Database;
}
}

namespace Ui {
class WorkingTimeItem;
}

class WorkingTimeItem : public QWidget
{
    Q_OBJECT

public:
    WorkingTimeItem();
    WorkingTimeItem(QString id);
    WorkingTimeItem(QString username, QDateTime start, QDateTime end, hypha::database::Database *database,  QWidget *parent = 0);
    WorkingTimeItem(QString username, QDateTime start, QDateTime end, QString type, hypha::database::Database *database, QWidget *parent = 0);
    WorkingTimeItem(QString id, QString username, QDateTime start, QDateTime end, QString type, hypha::database::Database *database, QWidget *parent = 0);
    ~WorkingTimeItem();

    void save();
    void deleteFromDatabase();

private:
    void init();
    Ui::WorkingTimeItem *ui;
    QString id;
    QString username;
    QDateTime start;
    QDateTime end;
    QString type;
    hypha::database::Database *database;
};

#endif // WORKINGTIMEITEM_H
