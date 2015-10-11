#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "../../plugin/hyphaplugin.h"
#include "../../plugin/pluginloader.h"
#include "../../database/database.h"
#include "../../database/userdatabase.h"
#include "serverstatus.h"

using namespace hypha::handler;
using namespace hypha::handler::serverstatus;
using namespace hypha::plugin;

ServerStatus::ServerStatus()
{
    serverStatusWidget = new ServerStatusWidget();
}

ServerStatus::~ServerStatus()
{

}

void ServerStatus::parse(QString message){

}

void ServerStatus::loadConfig(QString config)
{
    serverStatusWidget->loadConfig(config);
}

QString ServerStatus::getConfig()
{
    return serverStatusWidget->getConfig();
}

HyphaHandler *ServerStatus::getInstance(QString id, QObject *parent)
{
    ServerStatus *instance = new ServerStatus();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *ServerStatus::widget()
{
    return serverStatusWidget;
}
