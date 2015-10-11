#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "../../plugin/hyphaplugin.h"
#include "../../plugin/pluginloader.h"
#include "dooropener.h"
#include "../../database/database.h"
#include "../../database/userdatabase.h"


using namespace hypha::handler;
using namespace hypha::handler::dooropener;
using namespace hypha::plugin;

DoorOpener::DoorOpener()
{
    doorWidget = new DoorOpenerWidget();
}

DoorOpener::~DoorOpener()
{

}

void DoorOpener::parse(QString message){

}

void DoorOpener::loadConfig(QString config)
{
    doorWidget->setId(id);
    doorWidget->setDatabase(database);
    doorWidget->setUserDatabase(userDatabase);
    doorWidget->loadConfig(config);
}

QString DoorOpener::getConfig()
{
    return doorWidget->getConfig();
}

HyphaHandler *DoorOpener::getInstance(QString id, QObject *parent)
{
    DoorOpener *dooropener = new DoorOpener();
    dooropener->setParent(parent);
    dooropener->setId(id);
    return dooropener;
}

QWidget *DoorOpener::widget()
{
    return doorWidget;
}
