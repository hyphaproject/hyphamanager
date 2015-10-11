
#include <QtCore/QProcess>
#include <QtCore/QThread>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include "plugin/hyphaplugin.h"
#include "explorenfc.h"
#include "explorenfcwidget.h"

using namespace hypha::plugin::explorenfc;

void ExploreNFC::loadConfig(QString json)
{

}

QString ExploreNFC::getConfig()
{
    return "{}";
}

hypha::plugin::HyphaPlugin *ExploreNFC::getInstance(QString id, QObject *parent)
{
    ExploreNFC *instance = new ExploreNFC();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *ExploreNFC::widget()
{
    return new ExploreNFCWidget();
}

