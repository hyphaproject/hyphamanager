
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "email.h"

using namespace hypha::plugin;
using namespace hypha::plugin::email;

void EMail::loadConfig(QString json)
{
    widget();
    emailWidget->setHost(host);
    emailWidget->loadConfig(json);
}

QString EMail::getConfig()
{
    return emailWidget->getConfig();
}

HyphaPlugin *EMail::getInstance(QString id, QObject *parent)
{
    EMail *instance = new EMail();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *EMail::widget()
{
    if(!emailWidget)
        emailWidget = new EMailWidget();
    return emailWidget;
}
