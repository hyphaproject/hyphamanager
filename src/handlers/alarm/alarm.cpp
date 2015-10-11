#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "../../plugin/hyphaplugin.h"
#include "../../plugin/pluginloader.h"
#include "alarm.h"
#include "../../database/database.h"
#include "../../database/userdatabase.h"


using namespace hypha::handler;
using namespace hypha::handler::alarm;
using namespace hypha::plugin;

Alarm::Alarm()
{
	alarmWidget = new AlarmWidget();
}

Alarm::~Alarm()
{

}

void Alarm::parse(QString message){

}

void Alarm::loadConfig(QString config)
{
    alarmWidget->loadConfig(config);
}

QString Alarm::getConfig()
{
    return alarmWidget->getConfig();
}

HyphaHandler *Alarm::getInstance(QString id, QObject *parent)
{
    Alarm *instance = new Alarm();
    instance->setParent(parent);
    instance->setId(id);
    return instance;
}

QWidget *Alarm::widget()
{
    return alarmWidget;
}
