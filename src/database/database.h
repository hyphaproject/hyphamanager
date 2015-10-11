#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "../settings/databasesettings.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(DatabaseSettings * settings, QObject *parent = 0);
    ~Database();
    static Database *instance(DatabaseSettings *settings, QObject *parent);
    bool connect();
    QSqlQuery getQuery();


signals:

public slots:
private:

    void createTables();

    DatabaseSettings * settings;
    QSqlDatabase database;
};

#endif // DATABASE_H
