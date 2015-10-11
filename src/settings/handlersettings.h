#ifndef HANDLERSETTINGS_H
#define HANDLERSETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QMutex>

#include "../database/database.h"


class HandlerSettings : public QObject
{
    Q_OBJECT
public:
    explicit HandlerSettings(Database * database, QObject *parent = 0);
    QList<QString> getAllHandlerIds();
    QList<QString> getLocalHandlerIds();
    QString getName(QString id);
    QString getHost(QString id);
    QString getConfig(QString id);
    bool exists(QString id);

signals:

public slots:

private:

    ~HandlerSettings();
    Database * database;

};

#endif // HANDLERSETTINGS_H
