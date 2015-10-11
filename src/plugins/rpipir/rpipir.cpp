
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "plugin/hyphaplugin.h"
#include "rpipir.h"
#include "rpipirwidget.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpipir;

void RpiPir::loadConfig(QString json)
{
    widget();
    rpipirWidget->loadConfig(json);
}

QString RpiPir::getConfig()
{
    return rpipirWidget->getConfig();
}

HyphaPlugin *RpiPir::getInstance(QString id, QObject *parent)
{
    RpiPir *instance = new RpiPir();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *RpiPir::widget()
{
    if(!rpipirWidget)
        rpipirWidget = new RpiPirWidget();
    return rpipirWidget;
}
