#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QSettings>
#include <QtCore/QMutex>

class HyphaManagerSettings;

class DatabaseSettings : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseSettings(HyphaManagerSettings * clientSettings, QObject *parent = 0);
    ~DatabaseSettings();
    void save();
    QVariant getValue(const QString &key, const QVariant &defaultValue);
    void setValue(const QString &key, const QVariant &value);

    QString getDriver();
    QString getHost();
    QString getDatabase();
    QString getUser();
    QString getPassword();

signals:

public slots:

private:

    HyphaManagerSettings *managerSettings;

};

#endif // DATABASESETTINGS_H
