#ifndef HYPHAMANAGERSETTINGS_H
#define HYPHAMANAGERSETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QSettings>
#include <QtCore/QMutex>


class HyphaManagerSettings : public QObject
{
    Q_OBJECT
public:
    explicit HyphaManagerSettings(QString configfile, QObject *parent = 0);
    ~HyphaManagerSettings();
    void createNewFile();
    void load();
    void save();
    QVariant getValue(const QString &key, const QVariant &defaultValue);
	QVariant getValue(const QString &group, const QString &key, const QVariant &defaultValue);
    void setValue(const QString &group, const QString &key, const QVariant &value);

signals:

public slots:

private:
    QSettings *settings;
    QString configfile;

};

#endif // HYPHAMANAGERSETTINGS_H
