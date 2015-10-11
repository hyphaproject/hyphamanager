#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include "../../plugin/hyphaplugin.h"
#include "../../plugin/pluginloader.h"
#include "blechuhr.h"
#include "../../database/database.h"
#include "../../database/userdatabase.h"


using namespace hypha::handler;
using namespace hypha::handler::blechuhr;
using namespace hypha::plugin;

BlechUhr::BlechUhr()
{
    buwidget = new BlechUhrWidget();
}

BlechUhr::~BlechUhr()
{

}


void BlechUhr::parse(QString message){

}

void BlechUhr::loadConfig(QString config)
{

}

QString BlechUhr::getConfig()
{
    return "{\"name\":\"blechuhr\"}";
}

HyphaHandler *BlechUhr::getInstance(QString id, QObject *parent)
{
    BlechUhr *blechuhr = new BlechUhr();
    blechuhr->setParent(parent);
    blechuhr->setId(id);
    return blechuhr;
}

QWidget *BlechUhr::widget()
{
    return buwidget;
}
