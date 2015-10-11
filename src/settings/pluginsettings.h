#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QSettings>
#include <QtCore/QMutex>

#include "../database/database.h"


class PluginSettings : public QObject
{
    Q_OBJECT
public:
    explicit PluginSettings(Database *database, QObject *parent = 0);
    ~PluginSettings();
    QList<QString> getAllPluginIds();
    QList<QString> getLocalPluginIds();
    QString getName(QString id);
    QString getHost(QString id);
    QString getConfig(QString id);
    bool exists(QString id);

signals:

public slots:

private:
    Database *database;

};

#endif // PLUGINSETTINGS_H
